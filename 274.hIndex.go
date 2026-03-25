package main

import "sort"

func hIndex(citations []int) int {
	sort.Slice(citations, func(left int, right int) bool {
		return citations[left] > citations[right]
	})

	h := 0
	for ; h < len(citations); h++ {
		if citations[h] <= h {
			break
		}
	}

	return h
}
