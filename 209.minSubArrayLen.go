package main

func minSubArrayLen(target int, nums []int) int {
	left := 0
	right := 0
	size := len(nums)

	min_length := size + 1

	sum := 0

	for left < size {
		for right < size && sum < target {
			sum += nums[right]
			right++
		}

		if sum >= target {
			min_length = min(min_length, right-left)
		}

		sum -= nums[left]
		left++
	}

	if min_length > size {
		return 0
	}

	return min_length
}
