package main

func isValid(s string) bool {
	sz := len(s)

	stack := make([]byte, sz)
	top := -1

	for i := 0; i < sz; i++ {
		c := s[i]

		if c == '(' || c == '[' || c == '{' {
			top++
			stack[top] = c
		} else if top < 0 {
			return false
		} else if stack[top] == '(' && c == ')' {
			top--
		} else if stack[top] == '[' && c == ']' {
			top--
		} else if stack[top] == '{' && c == '}' {
			top--
		} else {
			return false
		}
	}

	return top == -1
}
