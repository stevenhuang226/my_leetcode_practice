package main

func minJumps(arr []int) int {
	size := len(arr)

	groups := make(map[int][]int)
	visitedValue := make(map[int]bool)

	for i := 0; i < size; i++ {
		value := arr[i]
		groups[value] = append(groups[value], i)
		visitedValue[value] = false
	}

	visited := make([]bool, size) // for index

	currQueue := []int{0}
	nextQueue := []int{0}

	step := -1

	nextQueue = append(nextQueue, 0)

	for len(nextQueue) > 0 {
		currQueue, nextQueue = nextQueue, currQueue[:0]
		step++

		for i := 0; i < len(currQueue); i++ {
			id := currQueue[i]
			value := arr[id]

			if id == size-1 {
				return step
			}

			if id-1 >= 0 && !visited[id-1] {
				visited[id-1] = true
				nextQueue = append(nextQueue, id-1)
			}

			if id+1 < size && !visited[id+1] {
				visited[id+1] = true
				nextQueue = append(nextQueue, id+1)
			}

			if visitedValue[value] {
				continue
			}

			visitedValue[value] = true

			for i2 := 0; i2 < len(groups[value]); i2++ {
				newId := groups[value][i2]
				if !visited[newId] {
					visited[newId] = true
					nextQueue = append(nextQueue, newId)
				}
			}
		}
	}

	return -1
}
