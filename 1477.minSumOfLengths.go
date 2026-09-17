package main

func minSumOfLengths(arr []int, target int) int {
	inf := 10000000

	best := make([]int, len(arr)+1)

	for i := range best {
		best[i] = inf
	}

	l := 0
	curr := 0

	bestSum := inf

	for r := 0; r < len(arr); r++ {
		curr += arr[r]
		for l < r && curr > target {
			curr -= arr[l]
			l++
		}

		best[r+1] = best[r]

		if curr != target {
			continue
		}

		ln := r - l + 1
		bestSum = min(bestSum, best[l]+ln)
		best[r+1] = min(best[r+1], ln)
	}

	if bestSum >= inf {
		return -1
	}

	return bestSum
}
