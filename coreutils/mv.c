
#include <stdio.h>

int main(int argc, char *argv[])
{
	int res;

	if (3 == argc) {
		res = rename(argv[1], argv[2]);
		if (-1 == res) {
			perror("rename");
			return 1;
		}
	} else {
		printf("usage: %s <source> <dest>\n", argv[0]);
		return 1;
	}

	return 0;
}
