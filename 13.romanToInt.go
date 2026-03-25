package main

func romanToInt(s string) int {
	size := len(s)

	sum := 0

	for i := 0; i < size; i++ {
		curr := s[i]
		next := byte(0)
		if i+1 < size {
			next = s[i+1]
		}

		if curr == 'I' {
			if next == 'V' {
				sum += 4
				i++
			} else if next == 'X' {
				sum += 9
				i++
			} else {
				sum += 1
			}
		} else if curr == 'V' {
			sum += 5
		} else if curr == 'X' {
			if next == 'L' {
				sum += 40
				i++
			} else if next == 'C' {
				sum += 90
				i++
			} else {
				sum += 10
			}
		} else if curr == 'L' {
			sum += 50
		} else if curr == 'C' {
			if next == 'D' {
				sum += 400
				i++
			} else if next == 'M' {
				sum += 900
				i++
			} else {
				sum += 100
			}
		} else if curr == 'D' {
			sum += 500
		} else if curr == 'M' {
			sum += 1000
		}
	}

	return sum
}
