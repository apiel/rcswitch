# RCswitch
Port of RCswitch for any kind of GPIO module (without WiringPi).

To compile the example run:

g++ -o  test test.cpp RCSwitch.cpp WProgram.cpp -std=c++0x -pthread

You can change the path of the gpio with setPathGpioData and setPathGpioPinMode.

