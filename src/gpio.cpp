
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


#include <gpio.h>

struct gpio_pin {
    bool in_out = false;
    int rd_wr_fd = -1;
    bool opened = false;
};

gpio_pin pins[26];

bool GPIO::openPin(int pin){
    int fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/export");
        close(fd);
        return false;
    }
    char * s;
    asprintf(&s, "%d", pin);


    if (write(fd, s, 2) != 2) {
        perror("Error writing to /sys/class/gpio/export");
        close(fd);
        return false;
    }

    free(s);
    asprintf(&s, "/sys/class/gpio/gpio%d/value", pin);
    pins[pin].rd_wr_fd = open(s, O_RDWR);
    pins[pin].opened = true;

    if(pins[pin].rd_wr_fd == -1){
        closePin(pin);
        return false;
    }

    return true;
}



bool GPIO::setPinMode(int pin, bool mode){
    char * s;
    asprintf(&s, "/sys/class/gpio/gpio%d/direction", pin);
    int fd = open(s, O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio24/direction");
        close(fd);
        return false;
    }

    if (write(fd, (mode ? "in" : "out"), 3) != 3) {
        perror("Error writing to /sys/class/gpio/gpio24/direction");
        close(fd);
        return false;
    }
    close(fd);

    pins[pin].in_out = mode;

    return true;
}



bool GPIO::setPinValue(int pin, bool value){
    if(pins[pin].rd_wr_fd == -1){
        char * s;
        asprintf(&s, "/sys/class/gpio/gpio%d/value", pin);
        pins[pin].rd_wr_fd = open(s, O_RDWR);
        pins[pin].opened = true;

        if(pins[pin].rd_wr_fd == -1){
            closePin(pin);
            return false;
        }
    }
    if (write(pins[pin].rd_wr_fd, (value ? "1": "0"), 1) != 1) {
        //perror("Error writing to /sys/class/gpio/gpio24/value");
        return false;
    }
    return true;
}

int GPIO::getPinValue(int pin){
    int out = -1;
    read(pins[pin].rd_wr_fd, &out, 1);
    return out;

}


bool GPIO::closePin(int pin){
    if(pins[pin].rd_wr_fd != -1){
        close(pins[pin].rd_wr_fd);
        pins[pin].rd_wr_fd = -1;
    }

    pins[pin].opened = false;

    int  fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/unexport");
        close(fd);
        return false;
    }

    char * s;
    asprintf(&s, "%d", pin);
    if (write(fd, s, 2) != 2) {
        perror("Error writing to /sys/class/gpio/unexport");
        close(fd);
        return false;
    }
    close(fd);



    return true;
}

int GPIO::getPinMode(int pin){
    if(pins[pin].opened){
        return pins[pin].in_out;
    }
    return -1;
}

bool GPIO::isPinOpened(int pin){
    return pins[pin].opened;
}

bool GPIO::closeAll(){

    for(int i = 0; i < 26; i ++ ){
        if(pins[i].opened){
            closePin(i);
        }
    }

    return true;
}


// int main()
// {
//     // Export the desired pin by writing to /sys/class/gpio/export

//     int fd = open("/sys/class/gpio/export", O_WRONLY);
//     if (fd == -1) {
//         perror("Unable to open /sys/class/gpio/export");
//         exit(1);
//     }

//     if (write(fd, "24", 2) != 2) {
//         perror("Error writing to /sys/class/gpio/export");
//         exit(1);
//     }

//     close(fd);

//     // Set the pin to be an output by writing "out" to /sys/class/gpio/gpio24/direction

//     fd = open("/sys/class/gpio/gpio24/direction", O_WRONLY);
//     if (fd == -1) {
//         perror("Unable to open /sys/class/gpio/gpio24/direction");
//         exit(1);
//     }

//     if (write(fd, "out", 3) != 3) {
//         perror("Error writing to /sys/class/gpio/gpio24/direction");
//         exit(1);
//     }

//     close(fd);

//     fd = open("/sys/class/gpio/gpio24/value", O_WRONLY);
//     if (fd == -1) {
//         perror("Unable to open /sys/class/gpio/gpio24/value");
//         exit(1);
//     }

//     // Toggle LED 50 ms on, 50ms off, 100 times (10 seconds)

//     for (int i = 0; i < 100; i++) {
//         if (write(fd, "1", 1) != 1) {
//             perror("Error writing to /sys/class/gpio/gpio24/value");
//             exit(1);
//         }
//         usleep(500000);

//         if (write(fd, "0", 1) != 1) {
//             perror("Error writing to /sys/class/gpio/gpio24/value");
//             exit(1);
//         }
//         usleep(500000);
//     }

//     close(fd);

//     // Unexport the pin by writing to /sys/class/gpio/unexport

//     fd = open("/sys/class/gpio/unexport", O_WRONLY);
//     if (fd == -1) {
//         perror("Unable to open /sys/class/gpio/unexport");
//         exit(1);
//     }

//     if (write(fd, "24", 2) != 2) {
//         perror("Error writing to /sys/class/gpio/unexport");
//         exit(1);
//     }

//     close(fd);

//     // And exit
//     return 0;
// }
