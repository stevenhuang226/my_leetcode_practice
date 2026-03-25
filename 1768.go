package main

import "fmt"

func mergeAlternately(word1 string, word2 string) string {
	lenL := len(word1)
	lenR := len(word2)

	ret := make([]byte, 0, lenL+lenR)

	indexL := 0
	indexR := 0

	for indexL < lenL || indexR < lenR {
		if indexL < lenL {
			ret = append(ret, word1[indexL])
			indexL++
		}
		if indexR < lenR {
			ret = append(ret, word2[indexR])
			indexR++
		}
	}

	return string(ret)
}

func main() {
	word1 := "abc"
	word2 := "pqr"

	fmt.Println(mergeAlternately(word1, word2))
}
