#
# Build mqtap shared library
#
# For Fedora, the path to librt.so is different, so comment the following line
# or run 'make CFLAGS=""'
#CFLAGS=-DRHEL
#


all:	lib/libmqtap.so lib64/libmqtap.so bin/mq_create bin/mq_send bin/mq_receive bin64/mq_create bin64/mq_send bin64/mq_receive

lib/libmqtap.so:	mq_tap.c
	gcc -Wall -O2 -fpic -shared -ldl -o lib/libmqtap.so mq_tap.c

lib64/libmqtap.so:	mq_tap.c 
	gcc -m64 -Wall -O2 -DLIB64 -fpic -shared -ldl -o lib64/libmqtap.so mq_tap.c

bin/mq_create:  mq_create.c
	gcc -g -o bin/mq_create mq_create.c -lrt

bin/mq_send:	mq_send.c
	gcc -g -o bin/mq_send mq_send.c -lrt

bin/mq_receive:	mq_receive.c
	gcc -g -o bin/mq_receive mq_receive.c -lrt

bin64/mq_create: mq_create.c
	gcc -m64 -g -o bin64/mq_create mq_create.c -lrt

bin64/mq_send:	mq_send.c
	gcc -m64 -g -o bin64/mq_send mq_send.c -lrt

bin64/mq_receive: mq_receive.c
	gcc -m64 -g -o bin64/mq_receive mq_receive.c -lrt

clean:
	rm -f *~ lib/* lib64/* bin/* bin64/*
