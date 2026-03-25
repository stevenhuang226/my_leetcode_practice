#include "shdstd-cpp.h"

class Solution
{
	public:
		bool isSubsequence(std::string s, std::string t)
		{
			int ps = 0;
			int pt = 0;

			int s_size = s.size();
			int t_size = t.size();

			while (ps < s_size && pt < t_size) {
				if (s[ps] == t[pt]) {
					++ps;
				}
				++pt;
			}

			return ps == s_size;
		}
};
