package main

func numOfWays(n int) int {
	mod := 1000000007

	last_same := 6
	last_diff := 6
	curr_same := 6
	curr_diff := 6

	for i := 1; i < n; i++ {
		curr_same = (last_same*3 + last_diff*2) % mod
		curr_diff = (last_same*2 + last_diff*2) % mod

		last_same = curr_same
		last_diff = curr_diff
	}

	return (curr_same + curr_diff) % mod
}
