package main

import "fmt"

func longestSubarray(nums []int) int {

	l := 0
	r := 0

	maximum := 0

	for r < len(nums) && nums[r] != 0 {
		r++
	}
	if r < len(nums) {
		maximum = r
	} else {
		maximum = r - 1
	}
	r++

	for r < len(nums) {
		if nums[r] == 0 {
			for nums[l] != 0 {
				l++
			}
			l++
		}

		maximum = max(maximum, r-l)
		r++
	}

	return maximum
}

func main() {
	var nums = []int{1, 1, 0, 1}
	res := longestSubarray(nums)

	fmt.Println(res)
}
