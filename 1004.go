package main

func longestOnes(nums []int, k int) int {
	l := 0
	r := 0

	zero_count := 0
	maxLength := 0

	for r < len(nums) {
		if nums[r] == 0 {
			zero_count++
		}
		r++

		for l < len(nums) && zero_count > k {
			if nums[l] == 0 {
				zero_count--
			}
			l++
		}

		maxLength = max(maxLength, r-l)
	}

	return maxLength
}
