//
// Created by grant on 8/5/16.
//

#include "RoboGarntSensors.h"


#define MAX_SENSE_RANGE 150

// ultrasonic sensors
#define US_GROUPS 2
#define US_PER_GROUP 2
PropWare::Ping us_sensors[US_GROUPS][US_PER_GROUP] = { // TODO: real pins
    {PropWare::Ping(PropWare::Port::P16, PropWare::Port::P17),
     PropWare::Ping(PropWare::Port::P18, PropWare::Port::P19)
    },
    {PropWare::Ping(PropWare::Port::P20, PropWare::Port::P21),
     PropWare::Ping(PropWare::Port::P22, PropWare::Port::P23)
    }
};

// adc pins
//#define ADC_OUT_PIN 24
//#define ADC_IN_PIN 25
//#define ADC_CLOCK_PIN 26
//#define ADC_SEL_PIN 27

// infrared sensors
#define IR_GROUPS 2
#define IR_PER_GROUP 4
const int ir_pins[IR_GROUPS][IR_PER_GROUP] = {  // TODO: real pins
    {0, 1, 2, 3} ,  // anterior
    {4, 5, 6, 7}   // posterior
};

// IR_COS[IR_PER_GROUP] = {cos(105), cos(75), cos(135), cos(45)}
//
// cos(45) = 0.70710678118
// cos(75) = 0.2588190451
// cos(105) = -0.2588190451
// cos(135) = -0.70710678118
const double IR_COS[IR_PER_GROUP] = {-0.2588, 0.2588, -0.7071, 0.7071};

// IR_SIN[IR_PER_GROUP] = {sin(105), sin(75), sin(135), sin(45)}
//
// sin(45) = 0.70710678118
// sin(75) = 0.96592582628
// sin(105) = 0.96592582628
// sin(135) = 0.70710678118
const double IR_SIN[IR_PER_GROUP] = {0.9659, 0.9659, 0.7071, 0.7071};
