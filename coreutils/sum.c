
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

/* block size for BSD and Sysv checksums */
#define BS_BSD 1024
#define BS_SYSV 512

#define READ_BYTES 4096

/* rotate right, 16-bit */
#define ror(x) (x >> 1) + ((x & 1) << 15)

int main(int argc, char *argv[])
{
	char *file;
	int fd;
	ssize_t size;
	uint8_t buf[READ_BYTES];
	uint16_t checksum16;
	uint32_t checksum32;
	unsigned int blocks;
	unsigned int bytes;
	unsigned int i;
	int bsd_sum = 1;

	if (argc != 2) {
		return 1;
	}
	file = argv[1];

	fd = open(file, O_RDONLY);
	if (-1 == fd) {
		perror("open");
		return 1;
	}

	checksum16 = 0;
	checksum32 = 0;
	bytes = 0;
	while (1) {
		size = read(fd, buf, sizeof(buf));
		if (0 == size) {
			// EOF
			break;
		} else if (size < 0) {
			perror("read");
			break;
		}

		for (i = 0; i < size; i++) {
			if (bsd_sum) {
				checksum16 = ror(checksum16);
				checksum16 += buf[i];
			} else {
				checksum32 += buf[i];
			}
		}

		if (! bsd_sum) {
			checksum16 = (checksum32 & 0xffff) + (checksum32 >> 16);
		}

		bytes += size;
	}
	close(fd);

	if (bsd_sum) {
		blocks = (bytes / BS_BSD) + ((bytes % BS_BSD) ? 1 : 0);
		printf("%05u  %4.u\n", checksum16, blocks);
	} else {
		blocks = (bytes / BS_SYSV) + ((bytes % BS_SYSV) ? 1 : 0);
		printf("%u %u\n", checksum16, blocks);
	}

	return 0;
}
