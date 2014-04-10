
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#define MAX_BYTES 1024

int main(int argc, char *argv[])
{
	int fd = NULL;
	uint8_t bytes[MAX_BYTES];
	ssize_t bytes_read;
	int i, j;

	unsigned int num_bytes;
	unsigned int num_lines;

	if (argc < 2) {
		printf("usage: %s [FILE]...\n", argv[0]);
		return EXIT_FAILURE;
	}

	for (i = 1; i < argc; i++) {

		fd = open(argv[i], O_RDONLY);
		if (-1 == fd) {
			perror("open");
			close(fd);
			return EXIT_FAILURE;
		}

		num_lines = 0;
		num_bytes = 0;
		while (1) {
			bytes_read = read(fd, &bytes, MAX_BYTES);
			if (-1 == bytes_read) {
				perror("open");
				close(fd);
				return EXIT_FAILURE;
			} else if (0 == bytes_read) {
				break;
			}
			for (j = 0; j < bytes_read; j++) {
				if ('\n' == bytes[j])
					num_lines++;
			}

			num_bytes += bytes_read;
		}

		close(fd);

		printf("%4d  %5d %s\n", num_lines, num_bytes, argv[i]);
	}

	return EXIT_SUCCESS;
}
