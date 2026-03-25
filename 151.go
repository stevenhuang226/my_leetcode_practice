package main

import "strings"

func reverseWords(s string) string {
	fields := strings.Fields(s)

	left := 0
	right := len(fields) - 1

	for left < right {
		fields[left], fields[right] = fields[right], fields[left]

		left++
		right--
	}

	return strings.Join(fields, " ")
}
