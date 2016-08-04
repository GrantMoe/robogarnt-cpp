//
// Created by grant on 8/3/16.
//
// #define MOTOR_PIN 0
// #define MOTOR_REVERSE_MIN 900
// #define MOTOR_NEUTRAL 1500
// #define MOTOR_DEADBAND 25
// #define MOTOR_FORWARD_MAX 2100
//
// #define MOTOR_PIN 0
// #define MOTOR_REVERSE_MIN 900
// #define MOTOR_NEUTRAL 1495
// #define MOTOR_DEADBAND 25
// #define MOTOR_FORWARD_MAX 2090
// #define THROTTLE_GAIN 3.7 // calibrated to stop when one sensor hits min

#ifndef ROBOPI_GARNT_CPP_ROBOGARNTMOTOR_H
#define ROBOPI_GARNT_CPP_ROBOGARNTMOTOR_H

class RoboGarntMotor {
 public:

  RoboGarntMotor (int, int, int, int, int, double);

  int LimitCheck (int);

  int get_pin() const { return pin_; }
  int get_reverse() const { return reverse_; }
  int get_min() const { return min_; }
  int get_neutral() const { return neutral_; }
  int get_deadband() const { return deadband_; }
  int get_forwards() const { return forwards_; }
  int get_max() const { return max_; }
  double get_throttle_gain() const { return throttle_gain_; }

  void set_pin (int pin) { pin_ = pin; }
  void set_reverse (int reverse) { reverse_ = reverse; }
  void set_min (int min) { min_ = min; }
  void set_neutral (int neutral) { neutral_ = neutral; }
  void set_deadband (int deadband) { deadband_ = deadband; }
  void set_forwards (int forwards) { forwards_ = forwards; }
  void set_max (int max) { max_ = max; }
  void set_throttle_gain (int gain) { throttle_gain_ = gain; }

 private:
  int pin_;
  int reverse_;
  int min_;
  int neutral_;
  int deadband_;
  int forwards_;
  int max_;
  double throttle_gain_;
};

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

#endif //ROBOPI_GARNT_CPP_ROBOGARNTMOTOR_H
