package main

import "fmt"

func getDescentPeriods(prices []int) int64 {
	if len(prices) == 1 {
		return 1
	}

	var sum = int64(1)

	var start = -1
	if prices[0]-prices[1] == 1 {
		start = 0
	} else {
		start = 1
	}

	for i := 1; i < len(prices); i++ {
		prev := prices[i-1]
		curr := prices[i]

		if prev-curr == 1 {
			sum += int64(i - start + 1)
		} else {
			start = i
			sum++
		}
	}

	return sum
}

func main() {
	var prices = []int{3, 2, 1, 4}
	fmt.Println(getDescentPeriods(prices))
}
