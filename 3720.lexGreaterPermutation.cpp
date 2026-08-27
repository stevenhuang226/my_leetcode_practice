#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	string lexGreaterPermutation(string s, string target) {
		vector<int> freq(26);

		for (char ch : s) {
			++freq[ch - 'a'];
		}

		string res(target.length(), ' ');
		bool bigger = false;
		bool backTrack = false;
		int ptr = 0;
		while (ptr < (int)target.length()) {
			if (ptr < 0) {
				return "";
			}

			int start = target[ptr] - 'a';

			if (backTrack) {
				++freq[res[ptr] - 'a'];
				++start;
			}
			if (bigger) {
				start = 0;
			}

			bool notFound = true;
			for (int i = start; i < 26; ++i) {
				if (! freq[i])
					continue;

				notFound = false;
				res[ptr] = i + 'a';
				--freq[i];

				if (i > target[ptr] - 'a') {
					bigger = true;
				}

				break;
			}

			if (!notFound && !bigger && ptr == target.length() - 1) {
				++freq[res[ptr] - 'a'];
				notFound = true;
			}

			if (notFound) {
				--ptr;
				backTrack = true;
				continue;
			}

			backTrack = false;
			++ptr;
		}

		return res;
	}
};
