package main

import (
	"fmt"
	"math"
)

func increasingTriplet(nums []int) bool {
	most_min := math.MaxInt
	second_min := math.MaxInt

	for i := 0; i < len(nums); i++ {
		num := nums[i]
		most_min = min(most_min, num)
		if most_min == num {
			continue
		}

		second_min = min(second_min, num)
		if second_min == num {
			continue
		}

		return true
	}

	return false
}

func main() {
	nums := []int{1, 2, 3, 4, 5}
	res := increasingTriplet(nums)
	fmt.Println(res)
}
