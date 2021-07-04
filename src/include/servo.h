#include <thread>
#include <gpio.h>


struct Servo {

    int pin = 0;
    double angle = 0;
    bool running = false;
    std::thread thread;
    Servo(int pin);

    bool start();

    bool stop();
    bool close();
};
