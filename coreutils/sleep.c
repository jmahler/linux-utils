
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	unsigned int s;

	if (argc >= 2) {
		s = atoi(argv[1]);
		sleep(s);
	}

	return 0;
}
