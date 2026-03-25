package main

import "fmt"

func pivotIndex(nums []int) int {
	suffix := 0
	for i := 0; i < len(nums); i++ {
		suffix += nums[i]
	}

	prefix := 0
	for i := 0; i < len(nums); i++ {
		prefix += nums[i]
		if prefix == suffix {
			return i
		}
		suffix -= nums[i]
	}

	return -1
}

func main() {
	nums := []int{1, 7, 3, 6, 5, 6}
	res := pivotIndex(nums)

	fmt.Println(res)
}
