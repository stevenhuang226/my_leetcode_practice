package main

func largestAltitude(gain []int) int {
	prefix := 0
	maximum := prefix

	for i := 0; i < len(gain); i++ {
		prefix += gain[i]
		maximum = max(maximum, prefix)
	}

	return maximum
}
