#include "shdstd-cpp.h"

class Solution
{
public:
	int maxRepeating(std::string sequence, std::string word)
	{
		int size = sequence.size();
		int trg_size = word.size();

		int range = size - trg_size;

		int maximum = 0;
		int p = 0;

		for (int i = 0; i <= range; ++i) {
			if (sequence[i] != word[0]) {
				continue;
			}
			p = 0;
			while(sequence[i + p] == word[p % trg_size]) {
				++p;
			}
			maximum = std::max(maximum, p / trg_size);
		}

		return maximum;
	}
};

int main()
{
	Solution solution;

	std::string sequence = "aaabaaaabaaabaaaabaaaabaaaabaaaaba";
	std::string trg = "aaaba";

	int res = solution.maxRepeating(sequence, trg);

	std::cout << res << std::endl;

	return 0;
}
