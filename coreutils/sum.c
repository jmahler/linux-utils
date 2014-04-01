
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

/* block size for BSD and Sysv checksums */
#define BS_BSD 1024
#define BS_SYSV 512

/* rotate right, 16-bit */
#define ror(x) (x >> 1) + ((x & 1) << 15)

int main(int argc, char *argv[])
{
	char *file;
	int fd;
	ssize_t res;
	uint8_t buf;
	uint16_t checksum;
	unsigned int blocks;
	unsigned int bytes;

	if (argc != 2) {
		return 1;
	}
	file = argv[1];

	fd = open(file, O_RDONLY);
	if (-1 == fd) {
		perror("open");
		return 1;
	}

	checksum = 0;
	bytes = 0;
	while (1) {
		res = read(fd, &buf, sizeof(buf));
		if (0 == res) {
			// EOF
			break;
		} else if (res < 0) {
			perror("read");
			return 1;
		}

		/* BSD Checksum */
		checksum = ror(checksum);
		checksum += buf;

		bytes++;
	}

	blocks = (bytes / BS_BSD) + ((bytes % BS_BSD) ? 1 : 0);
	printf("%05u  %4.u\n", checksum, blocks);

	return 0;
}
