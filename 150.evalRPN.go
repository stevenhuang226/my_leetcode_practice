package main

import "strconv"

func evalRPN(tokens []string) int {
	stack := make([]int, len(tokens))
	top := -1

	for i := 0; i < len(tokens); i++ {
		s := tokens[i]

		if s == "+" {
			stack[top-1] += stack[top]
			top--
		} else if s == "-" {
			stack[top-1] -= stack[top]
			top--
		} else if s == "*" {
			stack[top-1] *= stack[top]
			top--
		} else if s == "/" {
			stack[top-1] /= stack[top]
			top--
		} else {
			top++
			stack[top], _ = strconv.Atoi(s)
		}
	}

	if top != 0 {
		return -1
	}

	return stack[0]
}
