package main

func rotate(matrix [][]int) {
	rows := len(matrix)
	cols := len(matrix[0])

	for left := 0; left*2 < rows; left++ {
		right := rows - left - 1
		matrix[left], matrix[right] = matrix[right], matrix[left]
	}

	for r := 0; r < rows; r++ {
		for c := r + 1; c < cols; c++ {
			matrix[r][c], matrix[c][r] = matrix[c][r], matrix[r][c]
		}
	}
}
