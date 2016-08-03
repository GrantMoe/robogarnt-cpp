//
// Created by grant on 7/21/16.
//

#ifndef BASICGARNT_CONSTANTS_H
#define BASICGARNT_CONSTANTS_H

// robot anatomy
#define ANTERIOR 0
#define POSTERIOR 1
#define LEFT_MEDIAL 0
#define RIGHT_MEDIAL 1
#define LEFT_LATERAL 2
#define RIGHT_LATERAL 3

// TODO: meh.
// sensors
#define MAX_SENSE_RANGE 150

// ultrasonic sensors
#define US_GROUPS 2
#define US_PER_GROUP 2
PropWare::Ping us_sensors[US_GROUPS][US_PER_GROUP] = { // TODO: real pins
  {PropWare::Ping(PropWare::Port::P16, PropWare::Port::P17),
   PropWare::Ping(PropWare::Port::P18, PropWare::Port::P19)
  },
  {PropWare::Ping(PropWare::Port::P20, PropWare::Port::P21),
   PropWare::Ping(PropWare::Port::P22, PropWare::Port::P23)
  }
};

// adc pins
#define ADC_OUT_PIN 24
#define ADC_IN_PIN 25
#define ADC_CLOCK_PIN 26
#define ADC_SEL_PIN 27

// infrared sensors
#define IR_GROUPS 2
#define IR_PER_GROUP 4
const int ir_pins[IR_GROUPS][IR_PER_GROUP] = {  // TODO: real pins
  {0, 1, 2, 3} ,  // anterior
  {4, 5, 6, 7}   // posterior
};

// todo: meh? could be better with the -1 use for the ~cute~ multiplier.
// navigation
#define FORWARD 1
#define REVERSE -1
#define NAV_ARRAY_SIZE 4

struct Servo {
  int pin;
  int right_min;
  int neutral;
  int left_max;
  int steer_mode;
};

// PWM pins

//#define SERVO_MIN 1000
//#define SERVO_NEUTRAL 1500
//#define SERVO_MAX 2000

#define SERVO_MIN_ANTERIOR 1026
#define SERVO_NEUTRAL_ANTERIOR 1490
#define SERVO_MAX_ANTERIOR 1964
#define SERVO_MIN_POSTERIOR 1026
#define SERVO_NEUTRAL_POSTERIOR 1490
#define SERVO_MAX_POSTERIOR 1964

#define NUM_SERVOS 2
#define STEERING_GAIN 3.7

const int servo_pins[NUM_SERVOS] = {1 , 2};
Servo kAnteriorServo = {servo_pins[ANTERIOR],
                        SERVO_MIN_ANTERIOR,
                        SERVO_NEUTRAL_ANTERIOR,
                        SERVO_MAX_ANTERIOR};
Servo kPosteriorServo = {servo_pins[POSTERIOR],
                         SERVO_MIN_POSTERIOR,
                         SERVO_NEUTRAL_POSTERIOR,
                         SERVO_MAX_POSTERIOR};

Servo servos[NUM_SERVOS] = {kAnteriorServo, kPosteriorServo};

// TODO: deadbands
// #define MOTOR_PIN 0
// #define MOTOR_REVERSE_MIN 900
// #define MOTOR_NEUTRAL 1500
// #define MOTOR_FORWARD_MAX 2100
// #define MOTOR_DEADBAND 25
#define MOTOR_PIN 0
#define MOTOR_REVERSE_MIN 900
#define MOTOR_NEUTRAL 1495
#define MOTOR_FORWARD_MAX 2090
#define MOTOR_DEADBAND 25
#define THROTTLE_GAIN 3.7 // calibrated to stop when one sensor hits min

#endif //BASICGARNT_CONSTANTS_H
