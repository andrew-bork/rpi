#include <servo.h>
#include <gpio.h>
#include <cstdlib>
#include <unistd.h>
#include <iostream>

int main(int argc, char ** argv){
    int pin = 24;
    double angle = 90;

    if(argc >= 2){
        pin = atoi(argv[1]);
    }
    if(argc >= 3){
        angle = atof(argv[2]);
    }

    std::cout << "Rotating servo at pin " << pin << " to angle " << angle << " degrees.\n";


    Servo servo(pin);
    servo.start();
    servo.angle = angle;
    usleep(1000000);
    servo.stop();
    GPIO::closePin(pin);
}
