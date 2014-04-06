
#include <stdio.h>
#include <stdlib.h>

void usage(char *proc)
{
	printf("usage: %s [NUMBER]...\n", proc);
}

int main(int argc, char *argv[])
{
	int n;
	int i;
	int f;

	if (argc < 2) {
		usage(argv[0]);
		return 1;
	}

	for (i = 1; i < argc; i++) {
		n = atoi(argv[i]);

		printf("%d: ", n);
		f = 2;
		while (n > 1) {
			if (0 == (n % f)) {
				n = n / f;
				printf("%d ", f);
			} else {
				f++;
			}
		}
		printf("\n");
	}

	return 0;
}
