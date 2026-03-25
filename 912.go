package main

import "fmt"

func main() {
	nums := []int{5, 2, 3, 1, 4}
	sorted := sortArray(nums)
	fmt.Println("res:", sorted)
}

func sortArray(nums []int) []int {
	bfr := make([]int, len(nums))
	merge(nums, bfr, 0, len(nums))
	return nums
}

func merge(src []int, bfr []int, left int, right int) {
	if right-left <= 1 {
		return
	}

	mid := (left + right) / 2

	merge(src, bfr, left, mid)
	merge(src, bfr, mid, right)

	if src[mid-1] <= src[mid] {
		return
	}

	pl, pr := left, mid

	ptr := left

	for pl < mid && pr < right {
		if src[pl] < src[pr] {
			bfr[ptr] = src[pl]
			pl++
		} else {
			bfr[ptr] = src[pr]
			pr++
		}
		ptr++
	}

	for pl < mid {
		bfr[ptr] = src[pl]
		pl++
		ptr++
	}

	for pr < right {
		bfr[ptr] = src[pr]
		pr++
		ptr++
	}

	for i := left; i < right; i++ {
		src[i] = bfr[i]
	}

	return
}
