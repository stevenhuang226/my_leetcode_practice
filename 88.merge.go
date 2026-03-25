package main

func merge(numsa []int, m int, numsb []int, n int) {
	ptra := m - 1
	ptrb := n - 1
	write := m + n - 1

	for ptra >= 0 && ptrb >= 0 {
		if numsa[ptra] > numsb[ptrb] {
			numsa[write] = numsa[ptra]
			ptra--
		} else {
			numsa[write] = numsb[ptrb]
			ptrb--
		}
		write--
	}
	for ptra >= 0 {
		numsa[write] = numsa[ptra]
		ptra--
		write--
	}
	for ptrb >= 0 {
		numsa[write] = numsb[ptrb]
		ptrb--
		write--
	}
}
