package main

func spiralOrder(matrix [][]int) []int {
	rows := len(matrix)
	cols := len(matrix[0])

	rows--
	lim := cols

	R := 0
	C := -1

	resSize := len(matrix) * len(matrix[0])
	result := make([]int, resSize)
	w := 0

	dr := 0
	dc := 1

	for {
		if lim <= 0 {
			break
		}

		for i := 0; i < lim; i++ {
			R += dr
			C += dc
			result[w] = matrix[R][C]
			w++
		}

		if dr != 0 {
			rows--
			cols--
			lim = cols
		} else {
			lim = rows
		}

		tmp := dc
		dc = -(dr)
		dr = tmp
	}

	return result
}
