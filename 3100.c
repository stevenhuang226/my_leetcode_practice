int maxBottlesDrunk(int numBottles, int numExchange)
{
	int i;
	int res = 0;
	for (i = 0; i < INT_MAX; i++) {
		if (2*i*(numExchange-1) + (i-1)*i > 2 * numBottles) {
			res = i-1 + numBottles;
			break;
		}
	}

	return res;
}
