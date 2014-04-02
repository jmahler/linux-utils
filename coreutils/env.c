
#include <stdio.h>

int main()
{
	extern char **environ;
	char **p;

	for (p = environ; *p != NULL; p++) {
		printf("%s\n", *p);
	}

	return 0;
}
