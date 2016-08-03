#include <PropWare/sensor/distance/ping.h>
#include <math.h>

#include "libpropeller/pwm32/pwm32.h"

#include "Mcp3208.h"
#include "Constants.h"

int main() {

  int ir_voltages[IR_PER_GROUP];
  int ir_distances[IR_PER_GROUP];
  int us_distances[US_PER_GROUP];
  int nav_array[NAV_ARRAY_SIZE];

  int direction = FORWARD;
  kAnteriorServo.steer_mode = FORWARD;
  kPosteriorServo.steer_mode = REVERSE;
  int servo_setting;
  int motor_setting;

  Mcp3208 adc(ADC_OUT_PIN, ADC_IN_PIN, ADC_CLOCK_PIN, ADC_SEL_PIN);

  libpropeller::PWM32 pwm;
  pwm.Start();

  for(int fake_index = 0; fake_index < 42069; fake_index++) {

    // get IR voltages from adc
    for (int i = 0; i < IR_PER_GROUP; i++) {
      ir_voltages[i] = adc.ReadAdc(ir_pins[direction][i]);
    }
    // convert readings to distances
    // TODO: determine actual values
    for (int i = 0; i < IR_PER_GROUP; i++) {
      ir_distances[i] = (6787 / (ir_voltages[i] - 3)) - 4;
    }

    // get sonar
    for (int i = 0; i < US_PER_GROUP; i++) {
      us_distances[i] = us_sensors[direction][i].get_centimeters();
    }

    // calculate distances (using closest between uS and IR)
    for (int i = 0; i < NAV_ARRAY_SIZE; i++) {
      if (i < US_PER_GROUP)
        nav_array[i] = ir_distances[i] < us_distances[i] ? ir_distances[i]
                                                         : us_distances[i];
      else
        nav_array[i] = ir_distances[i];
    }

    // simple instinctual counter-steering
    // TODO: introduce speed modifier(s)?
    for (Servo s : servos) {
      // steer
      servo_setting = s.neutral + s.steer_mode * (int) (STEERING_GAIN * (
          ((MAX_SENSE_RANGE - nav_array[LEFT_LATERAL]) * cos(135))
              + ((MAX_SENSE_RANGE - nav_array[LEFT_MEDIAL]) * cos(105))
              + ((MAX_SENSE_RANGE - nav_array[RIGHT_MEDIAL]) * cos(75))
              + ((MAX_SENSE_RANGE - nav_array[RIGHT_LATERAL]) * cos(45))));

      if (servo_setting > s.left_max)
        servo_setting = s.left_max;
      if (servo_setting < s.right_min)
        servo_setting = s.right_min;

      // set servos
      pwm.Servo(s.pin, servo_setting);
    }

    // throttle
    if (direction == FORWARD) {
      motor_setting = MOTOR_FORWARD_MAX - (int) (THROTTLE_GAIN * (
        ((MAX_SENSE_RANGE - nav_array[LEFT_LATERAL]) * sin(135))
          + ((MAX_SENSE_RANGE - nav_array[LEFT_MEDIAL]) * sin(105))
          + ((MAX_SENSE_RANGE - nav_array[RIGHT_MEDIAL]) * sin(75))
          + ((MAX_SENSE_RANGE - nav_array[RIGHT_LATERAL]) * sin(45))));
      if (motor_setting < (MOTOR_NEUTRAL + MOTOR_DEADBAND)) {
        motor_setting = MOTOR_NEUTRAL;
        direction = REVERSE;
      }
    } else if (direction == REVERSE) {
      motor_setting = MOTOR_REVERSE_MIN + (int) (THROTTLE_GAIN * (
        ((MAX_SENSE_RANGE - nav_array[LEFT_LATERAL]) * sin(135))
          + ((MAX_SENSE_RANGE - nav_array[LEFT_MEDIAL]) * sin(105))
          + ((MAX_SENSE_RANGE - nav_array[RIGHT_MEDIAL]) * sin(75))
          + ((MAX_SENSE_RANGE - nav_array[RIGHT_LATERAL]) * sin(45))));
      if (motor_setting > (MOTOR_NEUTRAL - MOTOR_DEADBAND)) {
        motor_setting = MOTOR_NEUTRAL;
        direction = FORWARD;
      }
    } else {
      motor_setting = MOTOR_NEUTRAL;
    }

    // set motor
    pwm.Servo(MOTOR_PIN, motor_setting);
  }
  return 0;
}