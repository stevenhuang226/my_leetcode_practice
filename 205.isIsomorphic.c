#include "shdstd.h"

bool isIsomorphic(char *src, char *trg)
{
	int s2t[256];
	memset(s2t, 0xff, sizeof(s2t));
	int t2s[256];
	memset(t2s, 0xff, sizeof(t2s));

	int src_len = strlen(src);
	int trg_len = strlen(trg);

	if (src_len != trg_len) {
		return false;
	}

	for (int i = 0; i < src_len; ++i) {
		if (s2t[src[i]] > 0 || t2s[trg[i]] > 0) {
			if (s2t[src[i]] != trg[i] ||
				t2s[trg[i]] != src[i]) {
				return false;
			}
		}

		s2t[src[i]] = trg[i];
		t2s[trg[i]] = src[i];
	}

	return true;
}
