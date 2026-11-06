#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	struct interval {
		int endTime;
		int id;
	};
public:
	vector<int> countServers(int n, vector<vector<int>> &logs, int x, vector<int> &queries) {
		sort(logs.begin(), logs.end(), [](const vector<int> &a, const vector<int> &b) {
			return a[1] < b[1];
		});

		vector<interval> intervals(queries.size());
		for (int i = 0; i < queries.size(); ++i) {
			intervals[i].endTime = queries[i];
			intervals[i].id = i;
		}

		sort(intervals.begin(), intervals.end(), [](const interval &a, const interval &b) {
			return a.endTime < b.endTime;
		});

		vector<int> result(queries.size());
		vector<int> serverRecord(n, 0);
		int serverCount = 0;

		int left, right;
		left = right = 0;
		for (const interval &i : intervals) {
			int startTime = i.endTime - x;
			int endTime = i.endTime;
			int resId = i.id;

			while (left < logs.size() && logs[left][1] < startTime) {
				if (--serverRecord[logs[left][0] - 1] == 0) {
					--serverCount;
				}
				++left;
			}
			while (right < logs.size() && logs[right][1] <= endTime) {
				if (++serverRecord[logs[right][0] - 1] == 1) {
					++serverCount;
				}
				++right;
			}

			result[resId] = n - serverCount;
		}

		return result;
	}
};
