package main

func removeDuplicates(nums []int) int {
	wptr := 1
	rptr := 1

	size := len(nums)

	for rptr < size {
		if nums[rptr] != nums[rptr-1] {
			nums[wptr] = nums[rptr]
			wptr++
		}
		rptr++
	}

	return wptr
}
