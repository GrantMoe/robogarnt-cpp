//
// http://playground.arduino.cc/Code/MCP3208
//

#ifndef BASICGARNT_MCP3208_H
#define BASICGARNT_MCP3208_H

#define OUT 1
#define IN 0
#define HIGH 1
#define LOW 0

class Mcp3208
{
 public:
  Mcp3208(const int, const int, const int, const int);
  int ReadAdc(int);

 private:

  int out_pin_;
  int in_pin_;
  int clock_pin_;
  int select_pin_;
};

#endif //BASICGARNT_MCP3208_H

Mcp3208::Mcp3208(const int out_pin, const int in_pin, const int
clock_pin, const int select_pin) {

  // set pin numbers and modes
  out_pin_ = out_pin;
  in_pin_ = in_pin;
  clock_pin_ = clock_pin;
  select_pin_ = select_pin;

  set_direction(out_pin_, OUT);
  set_direction(in_pin_, IN);
  set_direction(clock_pin_, OUT);
  set_direction(select_pin_, OUT);

  //disable device to start with
  set_output(select_pin_, HIGH);
  set_output(out_pin_, LOW);
  set_output(clock_pin_, LOW);
}

int Mcp3208::ReadAdc(int channel){
  int adcvalue = 0;
  uint8_t command_bits = 192; //command bits (11000000) - start, mode, chn (3),
  // don't care (3)

  //allow channel selection
  command_bits|=((channel-1)<<3);

  low(select_pin_); // select adc
  // setup bits to be written
  for (int i=7; i>=3; i--){
    set_output(out_pin_, command_bits&1<<i);
    //cycle clock
    set_output(clock_pin_, HIGH);
    set_output(clock_pin_, LOW);
  }

  //ignores 2 null bits
  set_output(clock_pin_, HIGH);
  set_output(clock_pin_, LOW);
  set_output(clock_pin_, HIGH);
  set_output(clock_pin_, LOW);

  //read bits from adc
  for (int i=11; i>=0; i--){
    adcvalue+= (get_state(in_pin_) << i);
    //cycle clock
    set_output(clock_pin_, HIGH);
    set_output(clock_pin_, LOW);
  }
  set_output(select_pin_, HIGH); //turn off device
  return adcvalue;
}
