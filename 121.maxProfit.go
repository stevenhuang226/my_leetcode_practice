package main

const int32_max = (1 << 31) - 1
const int32_min = -1 << 31

func maxProfit(prices []int) int {
	min_price := int32_max
	max_profit := int32_min

	size := len(prices)

	for i := 0; i < size; i++ {
		min_price = min(min_price, prices[i])
		max_profit = max(max_profit, prices[i]-min_price)
	}

	return max_profit
}
