//
// Created by grant on 8/3/16.
//

#include "Servo.h"

Servo::Servo (int pin, int right_min, int neutral, int left_max, int steer_mode) {
  pin_ = pin;
  right_min_ = right_min;
  neutral_ = neutral;
  left_max_ = left_max;
  steer_mode_ = steer_mode;
}

int Servo::LimitCheck(int servo_setting) {
  if (servo_setting > left_max_)
    servo_setting = left_max_;
  if (servo_setting < right_min_)
    servo_setting = right_min_;
  return servo_setting;
}