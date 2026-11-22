#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	bool checkString(string s) {
		int8_t hasB = false;
		for (const char c : s) {
			if (hasB && c == 'a') {
				return false;
			}

			if (c == 'b')
				hasB = true;
		}

		return true;
	}
};
