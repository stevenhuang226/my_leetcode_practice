package main

func charCode(ch byte) int {
	if ch >= 'A' && ch <= 'Z' {
		return int(ch - 'A')
	} else {
		return int(ch-'a') + 26
	}
}

func minWindow(source string, target string) string {
	sourceLength := len(source)
	targetLength := len(target)

	bestLength := int(^uint(0) >> 1)
	bestStart := -1

	var targetFreq [52]int
	for i := 0; i < targetLength; i++ {
		cch := charCode(target[i])
		targetFreq[cch]++
	}

	var currFreq [52]int

	left := 0
	right := 0
	matchCount := 52

	for i := 0; i < 52; i++ {
		if targetFreq[i] > 0 {
			matchCount--
		}
	}

	for left < sourceLength {
		for matchCount != 52 && right < sourceLength {
			cch := charCode(source[right])
			currFreq[cch]++

			if currFreq[cch] == targetFreq[cch] {
				matchCount++
			}
			right++
		}

		currLen := right - left
		if matchCount == 52 && currLen < bestLength {
			bestLength = currLen
			bestStart = left
		}

		cch := charCode(source[left])
		if currFreq[cch] == targetFreq[cch] {
			matchCount--
		}
		currFreq[cch]--

		left++
	}

	if bestLength == int(^uint(0)>>1) {
		return ""
	}

	return source[bestStart : bestStart+bestLength]
}
