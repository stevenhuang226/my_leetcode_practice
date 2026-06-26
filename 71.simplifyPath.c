#include "shdstd.h"

int exp_max = 3e3 + 8;
char *simplifyPath(char *path)
{
	int *slash = malloc(exp_max * sizeof(int));
	int spp = 0;

	char *res = malloc(exp_max * sizeof(char));
	int rp = 0;

	char bfr[exp_max];
	int bp = 0;

	int len = strlen(path);
	for (int i = 0; i < len; ++i) {
		while (i < len && path[i] == '/') {
			++i;
		}
		if (i == len) break;

		while (i < len && path[i] != '/') {
			bfr[bp++] = path[i++];
		}
		bfr[bp] = '\0';

		if (strcmp(bfr, "..") == 0) {
			if (spp) {
				rp = slash[--spp];
			}
			bp = 0;
			continue;
		}
		if (strcmp(bfr, ".") == 0) {
			bp = 0;
			continue;
		}

		res[rp++] = '/';
		slash[spp++] = rp - 1;

		for (int i2 = 0; i2 < bp; ++i2) {
			res[rp++] = bfr[i2];
		}
		bp = 0;
	}

	free(slash);

	if (rp == 0) {
		res[rp++] = '/';
	}

	res[rp++] = '\0';
	return res;
}
