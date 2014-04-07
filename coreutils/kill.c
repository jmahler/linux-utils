
#include <sys/types.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void usage(char *proc)
{
	printf("usage: %s [-s <signal>] <pid>\n", proc);
}

int main(int argc, char *argv[])
{
	pid_t pid;
	int sig;
	int res;
	int opt;
	extern int optind;
	extern char *optarg;

	sig = SIGTERM;
	while ((opt = getopt(argc, argv, "s:")) != -1) {
		switch (opt) {
		case 's':
			sig = atoi(optarg);
			break;
		default:
			usage(argv[0]);
			return 1;
		}
	}
	/* PID is the first non-option argument */
	if (optind < argc) {
		pid = atoi(argv[optind]);
	} else {
		usage(argv[0]);
		fprintf(stderr, "  missing PID argument\n");
		return 1;
	}

	res = kill(pid, sig);
	if (-1 == res) {
		perror("kill");
		return 1;
	}

	return 0;
}
