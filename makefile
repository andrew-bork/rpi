
LIB_SRC:=${wildcard src/*.cpp}
BINARIES:=bin

.PHONY: all rotate servo_test

all: rotate servo_test

servo_test:
	g++ ${LIB_SRC} src/examples/servo_test.cpp -o ${BINARIES}/servo_test -Isrc/include -std=c++11 -pthread -lpthread
rotate:
	g++ ${LIB_SRC} src/examples/rotate.cpp -o ${BINARIES}/rotate -Isrc/include -std=c++11 -pthread -lpthread