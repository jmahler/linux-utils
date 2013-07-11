
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXBS 16384

int main(int argc, char* argv[])
{
	int i;
	char* arg;
	int err = 0;
	int ifd = STDIN_FILENO;
	int ofd = STDOUT_FILENO;
	char sbuf[256];
	int bs = 4096;
	int count = 100;
	char buf[MAXBS];
	ssize_t ret;
	size_t len;
	int j;

	/* dd if=<source> of=<dest> bs=<block size> count=N */
	for (i = 1; i < argc; i++) {
		arg = argv[i];

		if ( (strncmp(arg, "if=", 3)) == 0) {
			ifd = open((arg + 3), O_RDONLY);
			if (ifd == -1) {
				sprintf(sbuf, "%s: unable to open if=%s", argv[0], (arg + 3));
				perror(sbuf);
				err = 1;
				goto EXIT;
			}
		} else if ( (strncmp(arg, "of=", 3)) == 0) {
			ofd = open((arg + 3), O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (ofd == -1) {
				sprintf(sbuf, "%s: unable to open of=%s", argv[0], (arg + 3));
				perror(sbuf);
				err = 1;
				goto EXIT;
			}
		} else if ( (strncmp(arg, "bs=", 3)) == 0) {
			bs = atoi(arg + 3);

			if (bs > MAXBS) {
				fprintf(stderr, "%s: bs=%d is too large\n", argv[0], bs);
				err = 1;
				goto EXIT;
			}
		} else if ( (strncmp(arg, "count=", 6)) == 0) {
			count = atoi(arg + 6);
		}
	}

	for (i = 0; i < count; i++) {

		len = bs;
		j = 0;
		while ( (ret = read(ifd, (buf + j), len)) != 0) {
			if (ret == -1) {
				if (errno == EINTR)
					continue;
				perror("read");
				err = 1;
				goto EXIT;
			}

			len -= ret;
			j += ret;
		}

		len = j;
		j = 0;
		while (len != 0) {
			ret = write(ofd, &buf[j], len);
			if (ret == -1) {
				if (errno == EINTR)
					continue;
				perror("write");
				err = 1;
				goto EXIT;
			}

			len -= ret;
			j += ret;
		}

		// hit EOF
		if (j < bs)
			break;
	}

EXIT:
	close(ifd);
	close(ofd);

	return err;
}
