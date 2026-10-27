#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	vector<string> createGrid(int rows, int cols) {
		string firstLine = "";
		for (int c = 0; c < cols; ++c) {
			firstLine += ".";
		}

		vector<string> res;
		res.push_back(firstLine);

		for (int r = 1; r < rows; ++r) {
			string line = "";
			for (int c = 0; c < cols-1; ++c) {
				line += "#";
			}
			line += ".";

			res.push_back(line);
		}

		return res;
	}
};
