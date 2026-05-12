package main

func reverse(x int) int {
	res := 0
	for x > 0 {
		res *= 10
		res += x % 10
		x /= 10
	}
	return res
}

func abs(x int) int {
	if x < 0 {
		return -x
	} else {
		return x
	}
}

func mirrorDistance(n int) int {
	return abs(n - reverse(n))
}
