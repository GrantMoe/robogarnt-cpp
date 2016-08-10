//
// Created by grant on 8/5/16.
//

#ifndef ROBOPI_GARNT_CPP_ROBOGARNTSENSORS_H
#define ROBOPI_GARNT_CPP_ROBOGARNTSENSORS_H


class RoboGarntSensors {
 public:
  static constexpr double THROTTLE_GAIN = 3.7;

  RoboGarntSensors ();

  int get_pin() const { return pin_; }
  int get_reverse() const { return reverse_; }
  int get_min() const { return min_; }
  int get_neutral() const { return neutral_; }
  int get_deadband() const { return deadband_; }
  int get_forwards() const { return forwards_; }
  int get_max() const { return max_; }

  void set_pin (int pin) { pin_ = pin; }
  void set_reverse (int reverse) { reverse_ = reverse; }
  void set_min (int min) { min_ = min; }
  void set_neutral (int neutral) { neutral_ = neutral; }
  void set_deadband (int deadband) { deadband_ = deadband; }
  void set_forwards (int forwards) { forwards_ = forwards; }
  void set_max (int max) { max_ = max; }

 private:
  int pin_;
  int reverse_;
  int min_;
  int neutral_;
  int deadband_;
  int forwards_;
  int max_;
};


#endif //ROBOPI_GARNT_CPP_ROBOGARNTSENSORS_H
