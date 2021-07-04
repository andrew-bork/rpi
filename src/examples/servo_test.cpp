#include <servo.h>
#include <cstdlib>
#include <unistd.h>
#include <iostream>


int main(int argc, char ** argv){
    int pin = 24;
    double speed = 1;

    if(argc >= 2){
        pin = atoi(argv[1]);
    }
    if(argc >= 3){
        speed = atof(argv[2]);
    }

    GPIO::openPin(pin);
    GPIO::setPinMode(pin, GPIO_PINMODE_OUT);
    Servo servo(pin);

    std::cout << "Sweeping servo at pin " << pin << " at a speed of " << speed << ".\n";
    //servo.angle = 90;

    servo.start();



    double i = 0;
    double d = speed;
    int j = 0;
    while(j < 1000){
        servo.angle = i;
        i+=d;
        if(i >= 180) {d *= -1; i = 180;}
        if(i <= 0) {d *= -1; i = 0;}
        j++;
        usleep(10000);
    }

    servo.stop();
    GPIO::closePin(pin);
}