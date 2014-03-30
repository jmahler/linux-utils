
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#define MAXBUF 4096
#define MAXFILES 8

int main(int argc, char *argv[])
{
	int err = 0;
	ssize_t ret;
	size_t len;
	char buf[MAXBUF];
	int fd;
	int i;
	int fds[MAXFILES];
	int nfds;
	char *arg;
	char errbuf[128];

	nfds = 0;
	for (i = 1; i < argc; i++) {
		arg = argv[i];

		if (i > (MAXFILES - 1)) {
			fprintf(stderr, "too many files\n");
			err = 1;
			goto EXIT;
		}

		fd = open(arg, O_RDONLY);
		if (fd == -1) {
			sprintf(errbuf, "%s: unable to open %s", argv[0], arg);
			perror(errbuf);
			err = 1;
			goto EXIT;
		}

		fds[i-1] = fd;
		nfds++;
	}

	if (0 == nfds) {
		nfds = 1;
		fds[0] = STDIN_FILENO;
	}

	for (i = 0; i < nfds; i++) {
		fd = fds[i];

		while ( (ret = read(fd, buf, MAXBUF)) != 0) {
			if (ret == -1) {
				if (errno == EINTR)
					continue;
				perror("read");
				err = 1;
				goto EXIT;
			}
			len = ret;

			i = 0;
			while (len != 0) {
				ret = write(STDOUT_FILENO, &buf[i], len);
				if (ret == -1) {
					if (errno == EINTR)
						continue;
					perror("write");
					err = 1;
					goto EXIT;
				}

				len -= ret;
				i += ret;
			}
		}
	}

EXIT:

	for (i = 0; i < nfds; i++) {
		close(fds[i]);		
	}

	return err;
}
