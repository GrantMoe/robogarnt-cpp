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
#define FORWARD 0
#define REVERSE 1
#define NAV_ARRAY_SIZE 4

// PWM pins
// TODO: right vs left, rear vs front
#define SERVO_MIN 1000
#define SERVO_NEUTRAL 1500
#define SERVO_MAX 2000
#define NUM_SERVOS 2
#define STEERING_GAIN 3.7
const int servo_pins[NUM_SERVOS] = {1 , 2};

// TODO: deadbands
#define MOTOR_PIN 0
#define MOTOR_MIN 1000
#define MOTOR_NEUTRAL 1500
#define MOTOR_MAX 2000
#define THROTTLE_GAIN 3.7 // calibrated to stop when one sensor hits min

#endif //BASICGARNT_CONSTANTS_H
