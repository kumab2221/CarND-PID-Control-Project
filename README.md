
# CarND-Controls-PID  
[![Udacity - Self-Driving Car NanoDegree](https://s3.amazonaws.com/udacity-sdc/github/shield-carnd.svg)](http://www.udacity.com/drive)

## Overview  
---
The goal of this project is to go around the PID control course.

## Description  
---
The goals / steps of this project are the following:
- This code can be compiled  
- The PID procedure follows what was taught in the lesson  
- Explains the impact of the P, I, and D components on the implementation  
- Explains how the final hyperparameters were selected
- Vehicles can orbit trucks


## Using Library
---
- [JSON for Modern C++](https://github.com/nlohmann/json)  
  Template header library for connecting in JSON format

- [uWebSockets](https://github.com/uNetworking/uWebSockets)  
  This is dynamic library for communicating with Term2.
  To communicate with Term2, you need to compile something with a specific commit ID, and you can build your environment with the following command:
```
./install-ubuntu.sh
```
## Basic Build And Run Instructions
---
Enter the command in the top directory of the project according to the following procedure.  

1. Compile the edited code
    1. mkdir build
    1. cd build
    1. cmake ..
    1. make
    1. ./pid

    Alternatively some scripts have been included to streamline this process, these can be leveraged by executing the following in the top directory of the project:
    1. ./clean.sh
    1. ./build.sh
    1. ./run.sh
1. Start Term2 Simulator

## Requirement
---
### Environment for starting an Controls-PID Project
- cmake >= 3.5
  - All OSes: [click here for installation instructions](https://cmake.org/install/)
- make >= 4.1 (Linux, Mac), 3.81 (Windows)
  - Linux: make is installed by default on most Linux distros
  - Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  - Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
- gcc/g++ >= 5.4
  - Linux: gcc / g++ is installed by default on most Linux distros
  - Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  - Windows: recommend using [MinGW](http://www.mingw.org/)

### Simulator  
  This project involves the Term 2 Simulator which can be downloaded [here](https://github.com/udacity/self-driving-car-sim/releases).

## Communication protocol with the simulator  
---
Here is the main protocol that main.cpp uses for uWebSocketIO in communicating with the simulator.  

### INPUT: values provided by the simulator to the c++ program
// Data from the simulator
["cte"]            : Lateral distance between vehicle and trajectory
["speed"]          : Vehicle speed
["steering_angle"] : Vehicle steering angle

### OUTPUT: values provided by the c++ program to the simulator  
// Calculated value for use by the simulator  
["steering_angle"] : Input steering angle calculated based on cross-track error
["throttle"]       : Throttle value calculated to drive at a safe speed  

## Submission  
---
- [writeup.md](./writeup.md)
- [main.cpp](./src/main.cpp)
- [PID.cpp](./src/pid.cpp)
- [PID.h](./src/pid.h)

## Code Style  
---
Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Licence
---
[MIT](LICENSE)

## Author
---
[kumab2221](https://github.com/kumab2221)