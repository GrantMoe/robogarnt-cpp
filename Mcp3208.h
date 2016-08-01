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
