package main

func getCommon(numsa []int, numsb []int) int {
	ptra := 0
	ptrb := 0

	for ptra < len(numsa) && ptrb < len(numsb) {
		if numsa[ptra] == numsb[ptrb] {
			return numsa[ptra]
		}

		if numsa[ptra] > numsb[ptrb] {
			ptrb++
		} else {
			ptra++
		}
	}

	return -1
}
