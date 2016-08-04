cmake_minimum_required(VERSION 3.3)
find_package(PropWare REQUIRED)

include_directories(/usr/PropWare/include)

set(BOARD ROBOPI)

project(robopi_garnt_cpp CXX)

create_simple_executable(${PROJECT_NAME}
        RoboPiGarnt.cpp
        Mcp3208.h
        RoboGarntServo.h
        RoboGarntMotor.h)