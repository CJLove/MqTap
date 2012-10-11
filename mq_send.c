#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
	mqd_t	mqd;
	char	*ptr;
	size_t	len, i;
	unsigned	prio;

	if (argc != 4) {
		printf("usage: mq_send <name> <#bytes> <priority>\n");
        exit(-1);
    }
    
	len = atoi(argv[2]);
	prio = atoi(argv[3]);

	mqd = mq_open(argv[1], O_CREAT|O_WRONLY);

	ptr = calloc(len, sizeof(char));

    for (i = 0; i < len; ++i) {
        ptr[i] = i;
    }
    
	mq_send(mqd, ptr, len, prio);

	exit(0);
}
