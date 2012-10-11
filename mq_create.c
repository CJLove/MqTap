#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <unistd.h>

struct mq_attr	attr;	/* mq_maxmsg and mq_msgsize both init to 0 */

int
main(int argc, char **argv)
{
	int		c, flags;
	mqd_t	mqd;

	flags = O_RDWR | O_CREAT;
	while ( (c = getopt(argc, argv, "em:z:")) != -1) {
		switch (c) {
		case 'e':
			flags |= O_EXCL;
			break;

		case 'm':
			attr.mq_maxmsg = atol(optarg);
			break;

		case 'z':
			attr.mq_msgsize = atol(optarg);
			break;
		}
	}
	if (optind != argc - 1) {
		printf("usage: mqcreate [ -e ] [ -m maxmsg -z msgsize ] <name>\n");
        exit(-1);
    }

	if ((attr.mq_maxmsg != 0 && attr.mq_msgsize == 0) ||
		(attr.mq_maxmsg == 0 && attr.mq_msgsize != 0)) {
		printf("must specify both -m maxmsg and -z msgsize");
        exit(-1);
    }

	mqd = mq_open(argv[optind], flags,(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) ,
				  (attr.mq_maxmsg != 0) ? &attr : NULL);

	mq_close(mqd);
	exit(0);
}
