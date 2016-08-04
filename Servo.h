//
// Created by grant on 8/3/16.
//

#ifndef ROBOPI_GARNT_CPP_SERVO_H
#define ROBOPI_GARNT_CPP_SERVO_H

class Servo {
 public:

  Servo (int, int, int, int, int);

  int LimitCheck (int);

  int get_pin() const { return pin_; }
  int get_right() const { return right_min_; }
  int get_min() const { return right_min_; }
  int get_neutral() const { return neutral_; }
  int get_left() const { return left_max_; }
  int get_max() const { return left_max_; }
  int get_steer_mode() const { return steer_mode_; }

  void set_pin (int pin) { pin_ = pin; }
  void set_right (int right) { right_min_ = right; }
  void set_min (int min) { right_min_ = min; }
  void set_neutral (int neutral) { neutral_ = neutral; }
  void set_left (int left) { left_max_ = left; }
  void set_steer_mode (int steer_mode) { steer_mode_ = steer_mode; }

 private:
  int pin_;
  int right_min_;
  int neutral_;
  int left_max_;
  int steer_mode_;
};

#endif //ROBOPI_GARNT_CPP_SERVO_H
