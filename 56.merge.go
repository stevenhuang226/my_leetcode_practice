package main

import "sort"

func merge(intervals [][]int) [][]int {
	sort.Slice(intervals, func(l, r int) bool {
		if intervals[l][0] != intervals[r][0] {
			return intervals[l][0] < intervals[r][0]
		}
		return intervals[l][1] < intervals[r][1]
	})

	result := make([][]int, 0, len(intervals))

	start := intervals[0][0]
	end := intervals[0][1]

	for i := 1; i < len(intervals); i++ {
		currStart := intervals[i][0]
		currEnd := intervals[i][1]

		if currStart <= end {
			end = max(end, currEnd)
			continue
		}

		result = append(result, []int{start, end})

		start = currStart
		end = currEnd
	}

	result = append(result, []int{start, end})

	return result
}
