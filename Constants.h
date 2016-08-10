//
// Created by grant on 7/21/16.
//

#ifndef BASICGARNT_CONSTANTS_H
#define BASICGARNT_CONSTANTS_H

// navigation
#define FORWARD 0
#define REVERSE 1
#define NAV_ARRAY_SIZE 4
#define NORMAL 1
#define FLIPPED -1

// robot anatomy
#define ANTERIOR 0
#define POSTERIOR 1
#define LEFT_MEDIAL 0
#define RIGHT_MEDIAL 1
#define LEFT_LATERAL 2
#define RIGHT_LATERAL 3

#define POWER_PIN 4

// TODO: set
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
//#define ADC_OUT_PIN 24
//#define ADC_IN_PIN 25
//#define ADC_CLOCK_PIN 26
//#define ADC_SEL_PIN 27

// infrared sensors
#define IR_GROUPS 2
#define IR_PER_GROUP 4
const int ir_pins[IR_GROUPS][IR_PER_GROUP] = {  // TODO: real pins
  {0, 1, 2, 3} ,  // anterior
  {4, 5, 6, 7}   // posterior
};

// IR_COS[IR_PER_GROUP] = {cos(105), cos(75), cos(135), cos(45)}
//
// cos(45) = 0.70710678118
// cos(75) = 0.2588190451
// cos(105) = -0.2588190451
// cos(135) = -0.70710678118
const double IR_COS[IR_PER_GROUP] = {-0.2588, 0.2588, -0.7071, 0.7071};

// IR_SIN[IR_PER_GROUP] = {sin(105), sin(75), sin(135), sin(45)}
//
// sin(45) = 0.70710678118
// sin(75) = 0.96592582628
// sin(105) = 0.96592582628
// sin(135) = 0.70710678118
const double IR_SIN[IR_PER_GROUP] = {0.9659, 0.9659, 0.7071, 0.7071};


/*
struct Servo {
  int pin;
  int right_min;
  int neutral;
  int left_max;
  int steer_mode;
};

// PWM pins
// TODO: verify PWM ratings
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

// TODO: real pins
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
*/

#endif //BASICGARNT_CONSTANTS_H
