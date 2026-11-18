#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int minChanges(string s) {
		size_t len = s.length();

		if (len % 2) return -1;

		int changes = 0;
		for (int i = 0; i < len; i += 2) {
			if (s[i] != s[i+1]) ++changes;
		}

		return changes;
	}
};
