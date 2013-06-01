
CFLAGS =  -Wall

VPATH=$(dir $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST)))

all: testBMP085
testBMP085: testBMP085.c smbus.c

clean:
	$(RM) testBMP085 *.o
