package main

import "fmt"

func maxArea(height []int) int {
	l := 0
	r := len(height) - 1

	maximum := 0

	for l < r {
		h := min(height[l], height[r])
		maximum = max(maximum, h*(r-l))

		if height[l] < height[r] {
			l++
		} else {
			r--
		}
	}

	return maximum
}

func main() {
	var height = []int{1, 8, 6, 2, 5, 4, 8, 3, 7}
	res := maxArea(height)

	fmt.Println(res)
}
