CC=g++


all: control

control: RoboteqDevice.o
	$(CC) RoboteqDevice.o control.cpp -o control

RoboteqDevice.o: RoboteqDevice.cpp
	$(CC) -c RoboteqDevice.cpp

clean:
	rm *.o
