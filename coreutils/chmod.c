
#include <sys/stat.h>
#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	mode_t mode;
	char *file;

	if (3 != argc) {
		printf("usage: %s <mode> <file>\n", argv[0]);
		return 1;
	}
	if ( (sscanf(argv[1], "%o", &mode)) == 0) {
		fprintf(stderr, "invalid format\n");
		return 1;
	}
	file = argv[2];

	if ( (chmod(file, mode)) == -1) {
		error(1, errno, "chmod failed");
	}

	return 0;
}
