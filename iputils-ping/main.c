
#include <stdio.h>

#include "ping.h"

#define PDELAY 1

extern pid_t pid;

void sig_alrm()
{
	psend();

	alarm(PDELAY);

	return;
}

int main(int argc, char* argv[])
{
	int c;
	char* node;

	opterr = 0;
	while ( (c = getopt(argc, argv, "v")) != -1) {
		switch (c) {
		case 'v':
			break;
		case '?':
			fprintf(stderr, "unrecognized option: %s\n", argv[optind-1]);
			exit(EXIT_FAILURE);
		}
	}

	if (optind != (argc - 1)) {
		fprintf(stderr, "usage: %s [opts] <host>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	node = argv[optind];

	pid = getpid();

	pinit(node);

	signal(SIGALRM, sig_alrm);

	kill(pid, SIGALRM);		/* trigger first send */

	recvloop();

	exit(EXIT_SUCCESS);
}
