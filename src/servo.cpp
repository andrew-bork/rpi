#include <servo.h>
#include <gpio.h>
#include <unistd.h>
#include <iostream>

void servo_thread(Servo * servo){
    //int pw = 1000;
    int pw = (int) (2000 * servo -> angle / 180) + 500;
    int period = 20000;

    while(servo -> running){
        pw = (2000 * servo -> angle / 180) + 500;
        GPIO::setPinValue(servo->pin, GPIO_HIGH);
        usleep(pw);
        GPIO::setPinValue(servo->pin, GPIO_LOW);
        usleep(period - pw);
    }
}

Servo::Servo(int pin){
    this->pin = pin;

    if(!GPIO::isPinOpened(pin)){
        GPIO::openPin(pin);
    }

    GPIO::setPinMode(pin, GPIO_PINMODE_OUT);
}

bool Servo::start(){
    running = true;
    thread = std::thread (servo_thread, this);
    return true;
}

bool Servo::stop(){
    running = false;
    thread.join();
    return true;
}

bool Servo::close(){
    if(running) stop();
    GPIO::closePin(pin);
    return true;
}






