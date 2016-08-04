//
// Created by grant on 8/3/16.
//

#include "RoboGarntMotor.h"

RoboGarntMotor::RoboGarntMotor(int pin, int reverse_min, int neutral,
                               int deadband, int forwards_max,
                               double throttle_gain) {
  pin_ = pin;
  reverse_ = reverse_min;
  min_ = reverse_min;
  neutral_ = neutral;
  deadband_ = deadband;
  forwards_ = forwards_max;
  max_ = forwards_max;
  throttle_gain_ = throttle_gain;
}

int RoboGarntMotor::LimitCheck(int motor_setting) {
  if (motor_setting > max_)
    motor_setting = max_;
  if (motor_setting < min_)
    motor_setting = min_;
  return motor_setting;
}