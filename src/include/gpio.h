
#define GPIO_PINMODE_IN 1
#define GPIO_PINMODE_OUT 0

#define GPIO_HIGH 1
#define GPIO_LOW 0

namespace GPIO {

    bool openPin(int pin);
    bool setPinMode(int pin, bool mode);
    bool setPinValue(int pin, bool value);
    int getPinValue(int pin);
    bool closePin(int pin);
    int getPinMode(int pin);
    bool isPinOpened(int pin);

    bool closeAll();
}
