#include "shdstd-cpp.h"

using namespace std;

class ProductOfNumbers {
private:
	vector<int> numbers;
	int tp = -1;
	int prvZero = -1;
public:
	ProductOfNumbers() {
		int expMx = 4e4 + 8;
		numbers = vector<int>(expMx);
		numbers[++tp] = 1;
	}

	void add(int num) {
		int prv = numbers[tp];
		numbers[++tp] = max(prv*num, 1);

		if (num == 0) {
			prvZero = tp;
		}
	}

	int getProduct(int k) {
		if (tp-k < prvZero) return 0;

		return numbers[tp] / numbers[tp-k];
	}
};
