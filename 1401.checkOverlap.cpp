#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	struct Point {
		double x;
		double y;
	};

	double dist(const Point &a, const Point &b) {
		double x = abs(a.x - b.x);
		double y = abs(a.y - b.y);
		return sqrt(x * x + y * y);
	}
public:
	bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
		Point circleCenter = {(double)xCenter, (double)yCenter};

		Point closest;
		if (abs(y1 - yCenter) < abs(y2 - yCenter)) {
			closest.y = (double)y1;
		} else {
			closest.y = (double)y2;
		}

		if (abs(x1 - xCenter) < abs(x2 - xCenter)) {
			closest.x = (double)x1;
		} else {
			closest.x = (double)x2;
		}

		if ((xCenter < x1 && xCenter > x2) || (xCenter < x2 && xCenter > x1)) {
			closest.x = xCenter;
		}
		if ((yCenter < y1 && yCenter > y2) || (yCenter < y2 && yCenter > y1)) {
			closest.y = yCenter;
		}

		if (dist(circleCenter, closest) <= radius)
			return true;

		return false;
	}
};
