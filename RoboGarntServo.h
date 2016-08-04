//
// Created by grant on 8/3/16.
//
// Generic values:
// #define SERVO_MIN 1000
// #define SERVO_NEUTRAL 1500
// #define SERVO_MAX 2000
//
// #define SERVO_MIN_ANTERIOR 1026
// #define SERVO_NEUTRAL_ANTERIOR 1490
// #define SERVO_MAX_ANTERIOR 1964
// #define SERVO_MIN_POSTERIOR 1026
// #define SERVO_NEUTRAL_POSTERIOR 1490
// #define SERVO_MAX_POSTERIOR 1964

#ifndef ROBOPI_GARNT_CPP_ROBOGARNTSERVO_H
#define ROBOPI_GARNT_CPP_ROBOGARNTSERVO_H

class RoboGarntServo {
 public:

  RoboGarntServo (int, int, int, int, int, double);

  int LimitCheck (int);

  int get_pin() const { return pin_; }
  int get_right() const { return right_min_; }
  int get_min() const { return right_min_; }
  int get_neutral() const { return neutral_; }
  int get_left() const { return left_max_; }
  int get_max() const { return left_max_; }
  int get_steer_mode() const { return steer_mode_; }
  double get_steering_gain_() const { return steering_gain_; }

  void set_pin (int pin) { pin_ = pin; }
  void set_right (int right) { right_min_ = right; }
  void set_min (int min) { right_min_ = min; }
  void set_neutral (int neutral) { neutral_ = neutral; }
  void set_left (int left) { left_max_ = left; }
  void set_steer_mode (int steer_mode) { steer_mode_ = steer_mode; }
  void set_steering_gain (int steering_gain) { steering_gain_ = steering_gain; }

 private:
  int pin_;
  int right_min_;
  int neutral_;
  int left_max_;
  int steer_mode_;
  double steering_gain_;
};

#endif //ROBOPI_GARNT_CPP_ROBOGARNTSERVO_H

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