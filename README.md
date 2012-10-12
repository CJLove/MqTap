MqTap
=====
MqTap is a small "shim" library that can be interposed between
application code using POSIX message queues and the librt.so.1 shared
library which provides the mq_* function implementations.

The library is used by setting the LD_PRELOAD environment variable to
the full path to the libmq_tap:

    export LD_PRELOAD=/path/to/libmq_tap.so

You can then start your application(s) which use POSIX queues and calls
to mq_open(), mq_send(), mq_receive(), and mq_receive() will be
intercepted to allow for your own processing in addition to the
expected processing.

How It Works
============
Each mq function in the mq_tap library maintains a static function
pointer to the real mq function in the rt library; these pointers are
set on the first call by first loading the actual librt.so.1 library via
dlopen() and then calling dlsym() to get the address of the desired
function in that library.  The function pointers are then used to call
the actual implementation of the mq function before or after
"alternative" processing is performed.

The project makefile builds 32-bit and 64-bit versions of the mq_tap
library, as well as 32-bit and 64-bit versions of test code which
creates a queue, calls mq_send() and calls mq_receive().  

Applications
============
The overall intent of a library like this is to be able to tap into
POSIX message queues without modifying the application(s) using them.

In the base implementation of the mq_tap library all data passed to
mq_send() and received by mq_receive() will be logged to stdout.
Alternatives could include:
- logging the data to files in the mq_send() and mq_receive()
  functions
- creating a "shadow" message queue on each call to mq_open( O_CREAT) 
  and outputing the same data from each mq_send() to the shadow
  queue. 
- collecting queue usage statistics 

