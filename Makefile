#
# Build mqtap shared library
#
# For Fedora, the path to librt.so is different, so comment the following line
# or run 'make CFLAGS=""'
#CFLAGS=-DRHEL
#


all:	libmqtap.so

mq_tap.o:	mq_tap.c
	gcc -Wall -O2 -fpic -c ${CFLAGS} -o mq_tap.o mq_tap.c

libmqtap.so:	mq_tap.o 
	gcc -Wall -O2 -fpic -shared -ldl -o libmqtap.so mq_tap.o
#	/usr/bin/g++ -Wall -O2 -fpic -shared -ldl -o libmqtap.so mq_tap.c

clean:
	rm -f libmqtap.so *~ *.o
