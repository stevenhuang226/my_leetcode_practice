#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	struct wait {
		int weight;
		int id;

		bool operator>(const wait &other) const {
			if (weight != other.weight)
				return weight > other.weight;
			return id > other.id;
		}
	};

	struct busy {
		int64_t finish;
		wait server;

		bool operator>(const busy &other) const {
			if (finish != other.finish)
				return finish > other.finish;
			return server.id > other.server.id;
		}
	};
public:
	vector<int> assignTasks(vector<int> &servers, vector<int> &tasks) {
		priority_queue<
			wait,
			vector<wait>,
			greater<wait>
		> waiting;

		priority_queue<
			busy,
			vector<busy>,
			greater<busy>
		> busying;

		for (int i = 0; i < servers.size(); ++i) {
			waiting.push((wait){
				.weight = servers[i],
				.id = i
			});
		}

		vector<int> res(tasks.size());

		int64_t taskPtr = 0;
		int64_t curr = 0;
		while (taskPtr < tasks.size()) {
			if (waiting.empty())
				curr = busying.top().finish;

			while (!busying.empty() && busying.top().finish <= curr) {
				waiting.push(busying.top().server);
				busying.pop();
			}

			wait s = waiting.top();
			waiting.pop();

			res[taskPtr] = s.id;

			busying.push((busy){
				.finish = curr + tasks[taskPtr],
				.server = s
			});

			++taskPtr;
			curr = max(curr, taskPtr);
		}

		return res;
	}
};
