#include <PropWare/sensor/distance/ping.h>

#include "libpropeller/pwm32/pwm32.h"
#include "simpletools.h"
#include "Mcp3208.h"
#include "Constants.h"
#include "RoboGarntMotor.h"
#include "RoboGarntServo.h"

int main() {

  int ir_distances[IR_PER_GROUP];
  int us_distances[US_PER_GROUP];
  int nav_array[NAV_ARRAY_SIZE];

  int direction = FORWARD;

  RoboGarntServo anterior_servo(1, 1026, 1490, 1964, 3.7, NORMAL);
  RoboGarntServo posterior_servo(2, 1026, 1490, 1964, 3.7, FLIPPED);
  RoboGarntServo servos[] = {anterior_servo, posterior_servo};

  RoboGarntMotor motor(0, 900, 1495, 25, 2090, 3.7);

  int servo_setting;
  int motor_setting;

  Mcp3208 adc(ADC_OUT_PIN, ADC_IN_PIN, ADC_CLOCK_PIN, ADC_SEL_PIN);

  libpropeller::PWM32 pwm;
  pwm.Start();

  bool standby = input(POWER_PIN) == 0;

  for (int fake_index = 0; fake_index < 42069; fake_index++) {

    if (standby) {
      continue;
    }

    // get IR voltages from adc
    // convert readings to distances
    // TODO: determine actual values
    for (int i = 0; i < IR_PER_GROUP; i++) {
      ir_distances[i] = (6787 / (adc.ReadAdc(ir_pins[direction][i]) - 3)) - 4;
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
    anterior_servo.set_steer_mode(direction == FORWARD ? NORMAL : FLIPPED);
    posterior_servo.set_steer_mode(direction == FORWARD ? FLIPPED : NORMAL);

    //for (Servo s : servos) {
    for (int i = 0; i < 2; i++) {
      // steer
      servo_setting = servos[i].get_neutral() + servos[i].get_steer_mode()
          * (int) (servos[i].get_steering_gain_() * (
          ((MAX_SENSE_RANGE - nav_array[LEFT_LATERAL])
              * IR_COS[LEFT_LATERAL])
              + ((MAX_SENSE_RANGE - nav_array[LEFT_MEDIAL])
                  * IR_COS[LEFT_MEDIAL])
              + ((MAX_SENSE_RANGE - nav_array[RIGHT_MEDIAL])
                  * IR_COS[RIGHT_MEDIAL])
              + ((MAX_SENSE_RANGE - nav_array[RIGHT_LATERAL])
                  * IR_COS[RIGHT_LATERAL])));

      // set servos
      pwm.Servo(servos[i].get_pin(), servos[i].LimitCheck(servo_setting));
    }

    // throttle
    if (direction == FORWARD) {
      motor_setting = motor.get_max() - (int) (motor.get_throttle_gain() * (
        ((MAX_SENSE_RANGE - nav_array[LEFT_LATERAL])
            * IR_SIN[LEFT_LATERAL])
          + ((MAX_SENSE_RANGE - nav_array[LEFT_MEDIAL])
              * IR_SIN[LEFT_MEDIAL])
          + ((MAX_SENSE_RANGE - nav_array[RIGHT_MEDIAL])
              * IR_SIN[RIGHT_MEDIAL])
          + ((MAX_SENSE_RANGE - nav_array[RIGHT_LATERAL])
              * IR_SIN[RIGHT_LATERAL])));

      if (motor_setting < (motor.get_neutral() + motor.get_deadband())) {
        motor_setting = motor.get_neutral();
        direction = REVERSE;
      }

    } else if (direction == REVERSE) {
      motor_setting = motor.get_reverse() + (int) (motor.get_throttle_gain() * (
        ((MAX_SENSE_RANGE - nav_array[LEFT_LATERAL])
            * IR_SIN[LEFT_LATERAL])
          + ((MAX_SENSE_RANGE - nav_array[LEFT_MEDIAL])
              * IR_SIN[LEFT_MEDIAL])
          + ((MAX_SENSE_RANGE - nav_array[RIGHT_MEDIAL])
              * IR_SIN[RIGHT_MEDIAL])
          + ((MAX_SENSE_RANGE - nav_array[RIGHT_LATERAL])
              * IR_SIN[RIGHT_LATERAL])));

      if (motor_setting > (motor.get_neutral() - motor.get_deadband())) {
        motor_setting = motor.get_neutral();
        direction = FORWARD;
      }

    } else {
      motor_setting = motor.get_neutral();
    }

    // set motor
    pwm.Servo(motor.get_pin(), motor.LimitCheck(motor_setting));
  }
  return 0;
}