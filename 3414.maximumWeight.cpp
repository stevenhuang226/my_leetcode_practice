#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	struct State{
		int start;
		int end;
		int64_t weight;
		int index;
	};

	struct Result {
		int64_t score;
		vector<int> indices;
	};

	Result better(const Result &a, const Result &b) {
		if (a.score != b.score) {
			return a.score > b.score ? a : b;
		}

		return a.indices < b.indices ? a : b;
	}
public:
	vector<int> maximumWeight(vector<vector<int>> &srcIntervals) {
		int sz = srcIntervals.size();

		vector<State> intervals(sz);
		for (int i = 0; i < sz; ++i) {
			intervals[i].start = srcIntervals[i][0];
			intervals[i].end = srcIntervals[i][1];
			intervals[i].weight = srcIntervals[i][2];
			intervals[i].index = i;
		}
		sort(intervals.begin(), intervals.end(),
			[](const State &a, const State &b) {
				return a.end < b.end;
			});

		vector<int> prevNode(sz);
		for (int i = 0; i < sz; ++i) {
			int l = 0;
			int r = i - 1;
			while (l <= r) {
				int m = (l + r) / 2;
				if (intervals[m].end >= intervals[i].start) {
					r = m - 1;
				} else {
					l = m + 1;
				}
			}

			prevNode[i] = r;
		}

		vector<vector<Result>> maxScore(intervals.size() + 1, vector<Result>(4));

		for (int i = 0; i < sz; ++i) {
			Result take;
			take.score = intervals[i].weight;
			take.indices.push_back(intervals[i].index);

			for (int i2 = 0; i2 < 3; ++i2) {
				Result skip = maxScore[i][i2+1];
				Result take = maxScore[prevNode[i]+1][i2];

				take.score += intervals[i].weight;
				take.indices.push_back(intervals[i].index);

				sort(take.indices.begin(), take.indices.end());

				maxScore[i+1][i2+1] = better(skip, take);
			}
			maxScore[i+1][0] = better(maxScore[i][0], take);
		}

		return maxScore[sz][3].indices;
	}
};
