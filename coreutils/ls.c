
#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>

int streql(char* s1, char* s2)
{
	do {
		if (*s1 == '\0')
			if (*s2 == '\0')
				return 1;
			else
				return 0;
		else if (*s2 == '\0')
			return 0;

	} while (*(s1++) == *(s2++));

	return 0;
}

int main(int argc, char* argv[])
{
	int err = 0;
	char* name;
	DIR* dir;
	struct dirent* rdir;
	char sbuf[256];
	char* d_name;
	int all = 0;
	int i;
	char* arg;

	name = ".";
	for (i = 1; i < argc; i++) {
		arg = argv[i];

		if (arg[0] == '-') {
			if (streql(arg, "-a")) {
				all = 1;
			}
		} else {
			name = arg;
		}
	}

	dir = opendir(name);
	if (NULL == dir) {
		sprintf(sbuf, "%s: cannot access %s", argv[0], name);
		perror(sbuf);
		err = 1;
		goto EXIT1;
	}

	errno = 0;
	while( (rdir = readdir(dir)) != NULL) {
		d_name = rdir->d_name;

		if (streql(d_name, ".")) {
			continue;
		} else if (streql(d_name, "..")) {
			continue;
		} else if (!all && d_name[0] == '.') {
			continue;
		}

		printf("%s\n", d_name);
	}
	if (0 != errno) {
		perror("readdir");
		err = 1;
		goto EXIT1;
	}

EXIT1:
	closedir(dir);

	return err;
}

