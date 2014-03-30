
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int res;

	if (argc >= 2) {
		res = rmdir(argv[1]);
		if (-1 == res) {
			perror("rmdir");
			return 1;
		}
	}

	return 0;
}
