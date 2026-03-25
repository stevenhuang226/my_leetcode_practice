package main

import "sort"

const int32_max = (1 << 31) - 1

func minimumAbsDifference(arr []int) [][]int {
	size := len(arr)

	sort.Ints(arr)

	ret := make([][]int, size-1)

	minAbsDiff := int32_max

	for i := 0; i < size-1; i++ {
		diff := arr[i+1] - arr[i]

		if diff < minAbsDiff {
			minAbsDiff = diff
			ret = append(ret[:0], []int{arr[i], arr[i+1]})
			continue
		}
		if diff == minAbsDiff {
			ret = append(ret, []int{arr[i], arr[i+1]})
		}
	}

	return ret
}
