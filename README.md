MqTap
=====
MqTap is a small "shim" library that can be interposed between
application code using POSIX message queues and the librt.so.1 shared
library which provides the mq_* functions.

The library is used by setting the LD_PRELOAD environment variable to
the full path to the libmq_tap:

    export LD_PRELOAD=/path/to/libmq_tap.so

You can then start your application which uses POSIX queues and calls
to mq_send() and mq_receive() will be intercepted and the data logged
to stdout in hex and ASCII form. 





