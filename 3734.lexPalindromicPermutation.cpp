#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	bool checkStr(string &res, char center, const string &target) {
		int len = target.length();

		res[len/2] = center;

		for (int i = 0; i < len / 2; ++i) {
			int r = len-i-1;
			res[r] = res[i];
		}
		if (len%2 && center < target[len/2]) {
			return false;
		}
		for (int i = len / 2; i < len; ++i) {
			if (res[i] > target[i]) {
				return true;
			} else if (res[i] < target[i]) {
				return false;
			}
		}
		return false;
	}
public:
	string lexPalindromicPermutation(string s, string target) {
		if (target.length() == 1) {
			if (s[0] > target[0]) {
				return s;
			}
			return "";
		}

		vector<int> freq(26, 0);
		for (char ch : s) {
			++freq[ch-'a'];
		};

		int oddCount = 0;
		char center;
		for (int i = 0; i < freq.size(); ++i) {
			if (freq[i] % 2 == 1) {
				center = i + 'a';
				--freq[i];
				++oddCount;
			}
		}

		if (oddCount > 1) {
			return "";
		}

		int len = target.length();

		string res(len, ' ');

		bool bigger = false;
		bool backTrack = false;
		int ptr = 0;
		while (ptr < len / 2) {
			if (ptr < 0) {
				return "";
			}

			int start = target[ptr]-'a';

			if (backTrack) {
				freq[res[ptr]-'a'] += 2;
				++start;
			}
			if (bigger) {
				start = 0;
			}

			bool notFound = true;
			for (int i = start; i < 26; ++i) {
				if (freq[i] < 2)
					continue;

				notFound = false;
				res[ptr] = i+'a';
				freq[i] -= 2;

				if (i > target[ptr]-'a') {
					bigger = true;
				}
				break;
			}

			if (!notFound && !bigger &&
			ptr == len/2-1 &&
			!checkStr(res, center, target)) {
				freq[res[ptr]-'a'] += 2;
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

		checkStr(res, center, target);

		return res;
	}
};
