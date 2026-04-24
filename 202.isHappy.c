#include "shdstd.h"

int f(int n)
{
	int res = 0;
	while (n) {
		res += (n%10) * (n%10);
		n /= 10;
	}
	return res;
}

bool isHappy(int n)
{
	int slow, fast;
	slow = fast = n;
	do {
		slow = f(slow);
		fast = f(f(fast));
	} while (slow != fast);
	return slow == 1;
}
