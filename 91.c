#include "shdstd.h"

int numDecodings(char *s)
{
	if (s[0] == '0') {
		return 0;
	}

	int size = strlen(s);

	if (size == 1) {
		return 1;
	}

	int rdp[3] = {1,1,0};

	int i;
	for (i = 1; i < size; ++i) {
		rdp[2] = 0;

		int curr_num = s[i] - '0';
		if (curr_num != 0) {
			rdp[2] += rdp[1];
		}

		int coll_num = curr_num + (s[i-1] - '0') * 10;
		if (coll_num >= 10 && coll_num <= 26) {
			rdp[2] += rdp[0];
		}

		rdp[0] = rdp[1];
		rdp[1] = rdp[2];
	}

	return rdp[2];
}

int main()
{
	char *s1 = "12";
	char *s2 = "226";
	char *s3 = "06";
	char *s4 = "10";
	char *s5 = "2101";
//	printf("o:%d e:2\n", numDecodings(s1));
//	printf("o:%d e:3\n", numDecodings(s2));
//	printf("o:%d e:0\n", numDecodings(s3));
//	printf("o:%d e:1\n", numDecodings(s4));
	printf("o:%d e:1\n", numDecodings(s5));

	return 0;
}
