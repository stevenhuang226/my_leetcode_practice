package main

func maxDistance(colors []int) int {
	size := len(colors)

	mostLeft := colors[0]
	mostRight := colors[size-1]

	best := 0

	for L := 0; L < size; L++ {
		if colors[L] != mostRight {
			best = size - 1 - L
			break
		}
	}

	for R := size - 1; R >= 0; R-- {
		if colors[R] != mostLeft {
			best = max(best, R)
			break
		}
	}

	return best
}
