#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port
#include <cstdlib>

#include <cstdio>

#include <i2c.h>

int file_i2c = -1;
char buffer[60];

bool select_slave(int addr){
	if (ioctl(file_i2c, I2C_SLAVE, addr) < 0)
	{
		printf("Failed to acquire bus access and/or talk to slave.\n");
		//ERROR HANDLING; you can check errno to see what went wrong
		return false;
	}
    return true;
}

bool I2C::start(){
	char *filename = (char*)"/dev/i2c-1";
	if ((file_i2c = open(filename, O_RDWR)) < 0)
	{
		//ERROR HANDLING: you can check errno to see what went wrong
		printf("Failed to open the i2c bus");
		return false;
	}
    return true;
}

bool I2C::write_byte(int addr, int val){
    select_slave(addr);
	//----- WRITE BYTES -----
	buffer[0] = val;
	// buffer[1] = 0x02;
	int length = 1;			//<<< Number of bytes to write
	if (write(file_i2c, buffer, length) != length)		//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
	{
		/* ERROR HANDLING: i2c transaction failed */
		printf("Failed to write to the i2c bus.\n");
        return false;
	}
    return true;
}

int I2C::read_byte(int addr){
    select_slave(addr);
	if (read(file_i2c, buffer, 1) != 1)		//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
	{
		//ERROR HANDLING: i2c transaction failed
		printf("Failed to read from the i2c bus.\n");
        return -1;
	}

    return (int) buffer[0];
}

bool I2C::read(int addr, char * out, int len){
    select_slave(addr);

	if (read(file_i2c, out, len) != len)		//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
	{
		//ERROR HANDLING: i2c transaction failed
		printf("Failed to read from the i2c bus.\n");
        return false;
	}

    return true;
}
    // bool write_byte(int addr, int val);
    // int read_byte(int addr);

    // bool read(int addr, char * out, int len);

    // bool stop();