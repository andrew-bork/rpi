#include <cstdlib>
#include <i2c.h>

int main(int argc, char ** argv){

	bool opt = false;
	if(argc >= 2){
		opt = atoi(argv[1]) == 1;
	}

	int addr = 0x08;
	I2C::start();

	if(opt){
		I2C::write_byte(addr, 0x01);
	}else{
		I2C::write_byte(addr, 0x00);
	}
}