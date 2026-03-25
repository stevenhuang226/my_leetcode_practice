#include "shdstd.h"

#define MOD 1000000007
int numOfWays(int n)
{
	int64_t last_same = 6;
	int64_t last_diff = 6;
	int64_t curr_same = 6;
	int64_t curr_diff = 6;
	for (int i = 1; i < n; ++i) {
		curr_same = (last_same * 3 + last_diff * 2) % MOD;
		curr_diff = (last_same * 2 + last_diff * 2) % MOD;

		last_same = curr_same;
		last_diff = curr_diff;
	}

	return (int)((curr_same + curr_diff) % MOD);
}


/*

ABA
XYX
X == B => X: 1
Y != (B == X) => Y: 2
or
X != B && X != A => X: 1
Y != X && Y != B => Y: 1

ABA
XYZ
X != A => X: 2
Y != A && Y != B => Y: 1
Z != X && Z != Y => Z: 1


ABC
XYX
X != A && X != C => X: 1
Y != B => Y: 2

ABC
XYZ
X != A => X: 1
Y != X && Y != B => Y:1

ABC
XYZ
X != A => X: 2
Y != B && Y != X => Y: 1
Z != C && Z != Y => Z: 1

*/
