
#include <stdio.h>

int main(int argc, char* argv[])
{
	int i;
	char* file;
	int ret;
	char sbuf[256];

	if (1 == argc) {
		printf("%s: missing operand\n", argv[0]);
		return 1;
	}

	for (i = 1; i < argc; i++) {
		file = argv[i];

		ret = remove(file);
		if (-1 == ret) {
			sprintf(sbuf, "%s: cannot remove '%s'", argv[0], file);
			perror(sbuf);
		}
	}

	return 0;
}
