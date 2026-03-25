package main

import "sort"

func threeSum(nums []int) [][]int {
	size := len(nums)

	if size < 3 {
		return [][]int{}
	}

	sort.Ints(nums)

	if nums[0] > 0 {
		return [][]int{}
	}

	result := make([][]int, 0)

	for i := 0; i < size-2; i++ {
		if i > 0 && nums[i] == nums[i-1] {
			continue
		}

		left := i + 1
		right := size - 1

		for left < right {
			sum := nums[i] + nums[left] + nums[right]

			if sum < 0 {
				left++
				continue
			}
			if sum > 0 {
				right--
				continue
			}

			result = append(result, []int{
				nums[i], nums[left], nums[right],
			})
			left++
			for left < right && nums[left] == nums[left-1] {
				left++
			}
		}
	}

	return result
}
