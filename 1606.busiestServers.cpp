#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	struct busy {
		int finish;
		int id;

		bool operator>(const busy &other) const {
			return finish > other.finish;
		}
	};
public:
	vector<int> busiestServers(int serverCnt, vector<int> &arrival, vector<int> &load) {
		vector<int> serverWorkCount(serverCnt, 0);

		priority_queue<
			busy,
			vector<busy>,
			greater<busy>
		> busyServers;

		set<int> waiting;

		for (int i = 0; i < serverCnt; ++i) {
			waiting.insert(i);
		}

		size_t sz = arrival.size();
		for (int i = 0; i < sz; ++i) {
			int curr = arrival[i];
			int ld = load[i];

			while (!busyServers.empty() && busyServers.top().finish <= curr) {
				waiting.insert(busyServers.top().id);
				busyServers.pop();
			}

			if (waiting.empty())
				continue;

			auto it = waiting.lower_bound(i%serverCnt);
			if (it == waiting.end()) {
				it = waiting.begin();
			}

			int sid = *it;

			waiting.erase(it);
			busyServers.push((busy) {
				.finish = curr + ld,
				.id = sid
			});

			++serverWorkCount[sid];
		}

		int mx = 0;
		vector<int> res;
		for (int i = 0; i < serverCnt; ++i) {
			if (serverWorkCount[i] > mx) {
				res.clear();
				mx = serverWorkCount[i];
				res.push_back(i);
			} else if (serverWorkCount[i] == mx) {
				res.push_back(i);
			}
		}

		return res;
	}
};
