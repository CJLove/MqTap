#
# Build mqtap shared library
#
# For Fedora, the path to librt.so is different, so comment the following line
# or run 'make CFLAGS=""'
#CFLAGS=-DRHEL
#


all:	lib/libmqtap.so lib64/libmqtap.so

lib/mq_tap.o:	mq_tap.c
	gcc -Wall -O2 -fpic -c ${CFLAGS} -o lib/mq_tap.o mq_tap.c

lib/libmqtap.so:	lib/mq_tap.o 
	gcc -Wall -O2 -fpic -shared -ldl -o lib/libmqtap.so mq_tap.o

lib64/mq_tap.o:	mq_tap.c
	gcc -m64 -Wall -O2 -fpic -c ${CFLAGS} -o lib64/mq_tap.o mq_tap.c

lib64/libmqtap.so:	lib64/mq_tap.o 
	gcc -m64 -Wall -O2 -fpic -shared -ldl -o lib64/libmqtap.so mq_tap.o


clean:
	rm -f *~ lib/*.o lib/*.so lib64/*.o lib64/*.so
