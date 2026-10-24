#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	int monthDays(int month) {
		switch (month) {
			case 4:
			case 6:
			case 9:
			case 11:
				return 30;
			case 2:
				return 28;
			default:
				return 31;
		};
	}

	int dayInYear(int month, int day) {
		int cnt = 0;
		for (int i = 1; i < month; ++i) {
			cnt += monthDays(i);
		}
		return cnt + day;
	}
public:
	int countDaysTogether(string arriveA, string leaveA, string arriveB, string leaveB) {
		int arrCountA = dayInYear(
			stoi(arriveA.substr(0,2)),
			stoi(arriveA.substr(3,2))
		);

		int levCountA = dayInYear(
			stoi(leaveA.substr(0,2)),
			stoi(leaveA.substr(3,2))
		);

		int arrCountB = dayInYear(
			stoi(arriveB.substr(0,2)),
			stoi(arriveB.substr(3,2))
		);

		int levCountB = dayInYear(
			stoi(leaveB.substr(0,2)),
			stoi(leaveB.substr(3,2))
		);

		return max(0,
			min(levCountA, levCountB) -
			max(arrCountA, arrCountB) + 1
		);
	}
};
