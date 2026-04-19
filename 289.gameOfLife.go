package main

func gameOfLife(board [][]int) {
	rows := len(board)
	cols := len(board[0])

	dr := []int{-1, -1, 0, 1, 1, 1, 0, -1}
	dc := []int{0, 1, 1, 1, 0, -1, -1, -1}
	d_size := len(dr)

	var neighbors = make([][]int, rows)
	for i := 0; i < rows; i++ {
		neighbors[i] = make([]int, cols)
	}

	for r := 0; r < rows; r++ {
		for c := 0; c < cols; c++ {
			if board[r][c] != 1 {
				continue
			}
			for i := 0; i < d_size; i++ {
				nr := r + dr[i]
				nc := c + dc[i]

				if nr < 0 || nr >= rows {
					continue
				}
				if nc < 0 || nc >= cols {
					continue
				}

				neighbors[nr][nc]++
			}
		}
	}

	for r := 0; r < rows; r++ {
		for c := 0; c < cols; c++ {
			n_nerb := neighbors[r][c]

			if n_nerb < 2 {
				board[r][c] = 0
				continue
			}
			if n_nerb == 3 {
				board[r][c] = 1
				continue
			}
			if n_nerb > 3 {
				board[r][c] = 0
			}
		}
	}
}
