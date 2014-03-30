
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <fcntl.h>
#include <utime.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int ret;
	int i;
	char *file;

	if (1 == argc) {
		printf("%s: missing file operand\n", argv[0]);
		return 1;
	}

	for (i = 1; i < argc; i++) {
		file = argv[i];

		ret = utime(file, NULL);
		if (-1 == ret) {
			if (errno == ENOENT) {
				ret = creat(file, 0644);
				if (-1 == ret) {
					perror("creat");
					return 1;
				}
			} else {
				perror("utime");
				return 1;
			}
		}
	}

	return 0;
}
