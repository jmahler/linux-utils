
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int res;

	if (argc >= 2) {
		res = mkdir(argv[1], 0755);
		if (-1 == res) {
			perror("mkdir");
			return 1;
		}
	}

	return 0;
}
