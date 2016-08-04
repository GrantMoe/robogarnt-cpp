//
// http://playground.arduino.cc/Code/MCP3208
//
#include <PropWare/PropWare.h>
#include <PropWare/gpio/pin.h>

#ifndef BASICGARNT_MCP3208_H
#define BASICGARNT_MCP3208_H

class Mcp3208
{
 public:
  Mcp3208(const uint8_t, const uint8_t, const uint8_t, const uint8_t);
  int ReadAdc(int);

 private:

  PropWare::Pin out_pin_;
  PropWare::Pin in_pin_;
  PropWare::Pin clock_pin_;
  PropWare::Pin select_pin_;
};

#endif //BASICGARNT_MCP3208_H

Mcp3208::Mcp3208(const uint8_t out_pin, const uint8_t in_pin, const uint8_t
clock_pin, const uint8_t select_pin) {

  // set pin numbers and modes
  out_pin_ = PropWare::Pin(PropWare::Port::convert(out_pin),
                           PropWare::Pin::OUT);
  in_pin_ = PropWare::Pin(PropWare::Port::convert(in_pin),
                          PropWare::Pin::IN);
  clock_pin_ = PropWare::Pin(PropWare::Port::convert(clock_pin),
                             PropWare::Pin::OUT);
  select_pin_ = PropWare::Pin(PropWare::Port::convert(select_pin),
                              PropWare::Port::OUT);

  //disable device to start with
  select_pin_.high();
  out_pin_.low();
  clock_pin_.low();
}

int Mcp3208::ReadAdc(int channel){
  int adcvalue = 0;
  uint8_t command_bits = 192; //command bits (11000000) - start, mode, chn (3),
  // don't care (3)

  //allow channel selection
  command_bits|=((channel-1)<<3);

  select_pin_.low(); // select adc
  // setup bits to be written
  for (int i=7; i>=3; i--){
    out_pin_.write((command_bits&1<<i) == 1);
    //cycle clock
    clock_pin_.high();
    clock_pin_.low();
  }

  //ignores 2 null bits
  clock_pin_.high();
  clock_pin_.low();
  clock_pin_.high();
  clock_pin_.low();

  //read bits from adc
  for (int i=11; i>=0; i--){
    adcvalue+= in_pin_.read()? 1<<i : 0<<i;
    //cycle clock
    clock_pin_.high();
    clock_pin_.low();
  }
  select_pin_.high(); //turn off device
  return adcvalue;
}
