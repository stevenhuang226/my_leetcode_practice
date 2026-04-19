package main

func code(ch byte) int {
	return int(ch - 'a')
}

func isAnagram(src string, trg string) bool {
	src_len := len(src)
	trg_len := len(trg)

	if src_len != trg_len {
		return false
	}

	src_freq := [26]int{}
	trg_freq := [26]int{}

	for i := 0; i < src_len; i++ {
		src_ch := src[i]
		trg_ch := trg[i]

		src_freq[code(src_ch)]++
		trg_freq[code(trg_ch)]++
	}

	for i := 0; i < 26; i++ {
		if src_freq[i] != trg_freq[i] {
			return false
		}
	}

	return true
}
