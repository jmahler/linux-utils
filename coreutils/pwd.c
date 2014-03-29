
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {

	char *wd = NULL;

	wd = getcwd(NULL, 0);
	if (NULL == wd) {
		perror("getcwd");
		return 1;
	}

	printf("%s\n", wd);

	free(wd);
	
	return 0;
}
