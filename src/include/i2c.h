
namespace I2C {
    bool start();
    bool write_byte(int addr, int val);
    int read_byte(int addr);

    bool read(int addr, char * out, int len);
}