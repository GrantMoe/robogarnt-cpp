//
// Created by grant on 8/3/16.
//

#include "RoboGarntServo.h"

RoboGarntServo::RoboGarntServo (int pin, int right_min, int neutral,
                                int left_max, int steer_mode,
                                double steering_gain) {
  pin_ = pin;
  right_min_ = right_min;
  neutral_ = neutral;
  left_max_ = left_max;
  steer_mode_ = steer_mode;
  steering_gain_ = steering_gain;
}

int RoboGarntServo::LimitCheck(int servo_setting) {
  if (servo_setting > left_max_)
    servo_setting = left_max_;
  if (servo_setting < right_min_)
    servo_setting = right_min_;
  return servo_setting;
}