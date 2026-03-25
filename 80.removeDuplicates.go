package main

func removeDuplicates(nums []int) int {
	size := len(nums)

	if size <= 2 {
		return size
	}

	wptr := 2
	rptr := 2

	for rptr < size {
		if nums[rptr] != nums[wptr-2] {
			nums[wptr] = nums[rptr]
			wptr++
		}
		rptr++
	}

	return wptr
}
