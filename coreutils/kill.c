
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void usage(char *proc) {
	printf("usage: %s [options] <pid>\n", proc);
}

int main(int argc, char *argv[]) {

	pid_t pid;
	int sig;
	int res;

	if (argc < 2) {
		usage(argv[0]);
		return 1;
	}
	pid = atoi(argv[1]);

	sig = SIGTERM;
	res = kill(pid, sig);
	if (-1 == res) {
		perror("kill");
		return 1;
	}

	return 0;
}
