package main

func isIsomorphic(src string, trg string) bool {
	src_len := len(src)
	trg_len := len(trg)

	if src_len != trg_len {
		return false
	}

	s2t := [256]int{}
	t2s := [256]int{}
	for i := 0; i < 256; i++ {
		s2t[i] = -1
		t2s[i] = -1
	}

	for i := 0; i < src_len; i++ {
		s := src[i]
		t := trg[i]

		if s2t[s] > 0 || t2s[t] > 0 {
			if s2t[s] != int(t) || t2s[t] != int(s) {
				return false
			}
		}

		s2t[s] = int(t)
		t2s[t] = int(s)
	}

	return true
}
