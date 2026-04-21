package main

type UnionFind struct {
	parent []int
}

func NewUF(size int) *UnionFind {
	parent := make([]int, size)

	for i := 0; i < size; i++ {
		parent[i] = i
	}

	return &UnionFind{parent: parent}
}

func (uf *UnionFind) Find(target int) int {
	parent := uf.parent[target]

	if parent != target {
		uf.parent[target] = uf.Find(parent)
	}

	return uf.parent[target]
}

func (uf *UnionFind) Merge(left, right int) {
	leftRoot := uf.Find(left)
	rightRoot := uf.Find(right)

	if leftRoot == rightRoot {
		return
	}

	uf.parent[leftRoot] = rightRoot
}

func (uf *UnionFind) isConnected(left, right int) bool {
	return uf.Find(left) == uf.Find(right)
}

func minimumHammingDistance(
	source []int, target []int, swap [][]int) int {
	src_len := len(source)
	trg_len := len(target)

	exp_size := src_len + 8

	uf := NewUF(exp_size)

	for _, pair := range swap {
		left := pair[0]
		right := pair[1]

		uf.Merge(left, right)
	}

	comp := make(map[int]map[int]int)

	for i := 0; i < src_len; i++ {
		val := source[i]
		root := uf.Find(i)

		if comp[root] == nil {
			comp[root] = make(map[int]int)
		}

		comp[root][val]++
	}

	misMatch := 0

	for i := 0; i < trg_len; i++ {
		val := target[i]
		root := uf.Find(i)

		if comp[root][val] > 0 {
			comp[root][val]--
		} else {
			misMatch++
		}
	}

	return misMatch
}
