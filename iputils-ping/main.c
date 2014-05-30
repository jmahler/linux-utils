
#include <stdio.h>

#include "ping.h"

extern pid_t pid;
int ival = 1;

void sig_alrm()
{
	psend();

	if (ival > 0)
		alarm(ival);

	return;
}

int main(int argc, char* argv[])
{
	int c;
	char* node;
	struct sigaction sa;

	opterr = 0;
	while ( (c = getopt(argc, argv, "i")) != -1) {
		switch (c) {
		case 'i':
			ival = atoi(argv[optind]);
			break;
		case '?':
			fprintf(stderr, "unrecognized option: %s\n", argv[optind-1]);
			exit(EXIT_FAILURE);
		}
	}

	if (!(argc >= 2)) {
		fprintf(stderr, "usage: %s [opts] <host>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	node = argv[argc - 1];

	pid = getpid();

	pinit(node);

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sig_alrm;
	sigaction(SIGALRM, &sa, 0);

	kill(pid, SIGALRM);		/* trigger first send */

	while (1) {
		if (0 == ival)
			kill(pid, SIGALRM);

		precv();
	}

	exit(EXIT_SUCCESS);
}
