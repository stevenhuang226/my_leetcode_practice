#include "shdstd-cpp.h"

class Solution
{
	public:
		std::string mergeAlternately(std::string word1, std::string word2)
		{
			std::string ret = "";

			int l, r;
			l = r = 0;

			while (l < word1.length() && r < word2.length()) {
				ret += word1[l++];
				ret += word2[r++];
			}

			while (l < word1.length()) {
				ret += word1[l++];
			}

			while (r < word2.length()) {
				ret += word2[r++];
			}

			return ret;
		}
};
