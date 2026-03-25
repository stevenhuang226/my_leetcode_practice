package main

func majorityElement(nums []int) int {
	times := 0
	id := -1

	for i := 0; i < len(nums); i++ {
		num := nums[i]

		if times == 0 {
			id = num
		}

		if id != num {
			times--
		} else {
			times++
		}
	}

	return id
}
