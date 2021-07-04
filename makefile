
LIB_SRC:=${wildcard src/*.cpp}
BINARIES:=bin

.PHONY: all rotate servo_test i2c_arduino

all: rotate servo_test i2c_arduino

servo_test:
	mkdir ${BINARIES}
	g++ ${LIB_SRC} src/examples/servo_test.cpp -o ${BINARIES}/servo_test -Isrc/include -std=c++11 -pthread -lpthread
rotate:
	mkdir ${BINARIES}
	g++ ${LIB_SRC} src/examples/rotate.cpp -o ${BINARIES}/rotate -Isrc/include -std=c++11 -pthread -lpthread

i2c_arduino:
	mkdir ${BINARIES}
	g++ ${LIB_SRC} src/examples/i2c_arduino.cpp -o ${BINARIES}/i2c_arduino -Isrc/include -std=c++11 -pthread -lpthread

static:
	mkdir build
	mkdir ${BINARIES}
	g++ -c {LIB_SRC} -o build/rpi.o -Isrc/include -std=c++11 -pthread -lpthread
	ar rcs ${BINARIES}/librpi.a build/rpi.o