package main

import "sort"

func groupAnagrams(strs []string) [][]string {
	groups := make(map[string][]string)

	for _, word := range strs {
		bytes := []byte(word)
		sort.Slice(bytes, func(L, R int) bool {
			return bytes[L] < bytes[R]
		})

		key := string(bytes)
		groups[key] = append(groups[key], word)
	}

	result := make([][]string, 0, len(groups))
	for _, group := range groups {
		result = append(result, group)
	}

	return result
}
