
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	unsigned long start, end;

	if (argc != 3) {
		fprintf(stderr, "usage: %s <start> <end>\n", argv[0]);
		return 1;
	}
	start = atoll(argv[1]);
	end = atoll(argv[2]);

	for (unsigned long i = start; i <= end; i++) {
		printf("%lu\n", i);
	}

	return 0;
}
