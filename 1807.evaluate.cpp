#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	string evaluate(string s, vector<vector<string>> &knowledge) {
		unordered_map<string, string> change;
		for (vector<string> k : knowledge) {
			change[k[0]] = k[1];
		}

		string res = "";

		for (int i = 0; i < s.length(); ++i) {
			if (s[i] != '(') {
				res += s[i];
				continue;
			}

			string n = "";

			++i;
			while (s[i] != ')') {
				n += s[i++];
			}

			auto it = change.find(n);

			if (it == change.end()) {
				res += "?";
			} else {
				res += it->second;
			}
		}

		return res;
	}
};
