package main

func candy(ratings []int) int {
	size := len(ratings)
	candies := make([]int, size)

	for left := 0; left < size-1; left++ {
		if ratings[left+1] > ratings[left] {
			candies[left+1] = candies[left] + 1
		}
	}

	sum := size

	for right := size - 2; right >= 0; right-- {
		sum += candies[right+1]

		if ratings[right] > ratings[right+1] {
			candies[right] = max(candies[right], candies[right+1]+1)
		}
	}
	sum += candies[0]

	return sum
}

func main() {
}
