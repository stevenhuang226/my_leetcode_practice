#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	set<string> ans;
	string expr;

	void dfs(string s) {
		size_t r = s.find('}');
		if (r == string::npos) {
			ans.insert(s);
			return;
		}

		size_t l = s.rfind('{', r);

		string lstr = s.substr(0, l);
		string rstr = s.substr(r + 1);

		string center = s.substr(l+1, r-l-1);

		string part;
		stringstream ss(center);

		while (getline(ss, part, ',')) {
			dfs(lstr + part + rstr);
		}
	}

public:
	vector<string> braceExpansionII(string expression) {
		dfs(expression);

		return vector<string>(ans.begin(), ans.end());
	}
};
