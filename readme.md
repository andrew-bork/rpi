# RPI
A simple C++ library to control some functions of the GPIO header in the RPI. Current supports
- Standard GPIO
- Servo (PWM) control
- I2C control

## Build
just run
```
make
```
in the directory installed to build the examples

## Using the library
- Copy the src folder items (minus the examples) and make sure src/include is an include path when compiling.
- Build the library into a static library

## Run the examples
examples may need `sudo`
### rotate
builds in `bin/rotate`
usage: `./rotate [pin-num (defaults to 24)] [angle (defaults to 90)]`
just rotates the servo at a pin to an angle
### servo_test
builds in `bin/servo_test`
usage: `./servo_test [pin-num (defaults to 24)] [sweep speed (defaults to 1)]`
just sweeps the servo for a few seconds.
### i2c_arduino
builds in `bin/i2c_arduino`
requires a specific configuration of the raspberry pi and an arduino
usage: `./i2c_arduino [0|1 (defaults to 0)]`
not very useful to the average GPIO user.