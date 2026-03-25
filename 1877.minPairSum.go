package main

import "sort"

func minPairSum(nums []int) int {
	sort.Slice(nums, func(left, right int) bool {
		return nums[left] < nums[right]
	})

	left := 0
	right := len(nums) - 1

	max_num := 0

	for left < right {
		max_num = max(max_num, nums[left]+nums[right])
		left++
		right--
	}

	return max_num
}
