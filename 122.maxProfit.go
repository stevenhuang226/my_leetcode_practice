package main

func maxProfit(prices []int) int {
	profit := 0
	size := len(prices)

	for i := 0; i < size-1; i++ {
		tmp := prices[i+1] - prices[i]

		if tmp > 0 {
			profit += tmp
		}
	}

	return profit
}
