package main

func code(ch byte) int {
	return int(ch - 'a')
}

func canConstruct(target string, source string) bool {
	trg_len := len(target)
	src_len := len(source)

	trg_freq := [26]int{}
	src_freq := [26]int{}

	for i := 0; i < trg_len; i++ {
		trg_freq[code(target[i])]++
	}
	for i := 0; i < src_len; i++ {
		src_freq[code(source[i])]++
	}
	for i := 0; i < 26; i++ {
		if trg_freq[i] > src_freq[i] {
			return false
		}
	}

	return true
}
