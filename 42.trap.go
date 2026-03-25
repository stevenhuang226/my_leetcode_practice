package main

func trap(height []int) int {
	trapped := 0

	left := 0
	right := len(height) - 1

	left_max := 0
	right_max := 0

	for left < right {
		if height[left] < height[right] {
			left_max = max(left_max, height[left])
			trapped += left_max - height[left]
			left++
		} else {
			right_max = max(right_max, height[right])
			trapped += right_max - height[right]
			right--
		}
	}

	return trapped
}
