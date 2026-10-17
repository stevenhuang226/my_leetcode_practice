#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int minSwaps(vector<int> &nums) {
		vector<int> digitSum(nums.size());
		vector<int> resIdx(nums.size());
		for (int i = 0; i < nums.size(); ++i) {
			int n = nums[i];
			int sum = 0;
			while (n) {
				sum += n % 10;
				n /= 10;
			}
			digitSum[i] = sum;

			resIdx[i] = i;
		}

		sort(resIdx.begin(), resIdx.end(), [&](int a, int b) {
			if (digitSum[a] != digitSum[b]) {
				return digitSum[a] < digitSum[b];
			}
			return nums[a] < nums[b];
		});

		vector<bool> visited(nums.size(), false);
		int cycle = 0;
		for (int i = 0; i < nums.size(); ++i) {
			if (visited[i])
				continue;

			++cycle;
			visited[i] = true;
			int nxt = resIdx[i];
			while (!visited[nxt]) {
				visited[nxt] = true;
				nxt = resIdx[nxt];
			}
		}

		return nums.size() - cycle;
	}
};
