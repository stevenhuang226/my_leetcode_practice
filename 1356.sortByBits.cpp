#include "shdstd-cpp.h"

using namespace std;

class Solution {
	public:
		vector<int> sortByBits(vector<int>& arr) {
			vector<vector<int>> diff_bits(32, vector<int>());

			int size = arr.size();

			sort(arr.begin(), arr.end());

			for (int i = 0; i < size; ++i) {
				int num = arr[i];
				int bits_count = 0;
				int tmp = num;
				while (tmp) {
					bits_count += tmp & 0x01;
					tmp >>= 1;
				}

				diff_bits[bits_count].push_back(num);
			}

			vector<int> res(size);
			int resptr = 0;

			for (int bits = 0; bits < 32; ++bits) {
				int bits_count_size = diff_bits[bits].size();
				for (int i = 0; i < bits_count_size; ++i) {
					res[resptr++] = diff_bits[bits][i];
				}
			}

			return res;
		}
};
