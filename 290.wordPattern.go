package main

import "strings"

func wordPattern(pattern string, src string) bool {
	words := strings.Fields(src)

	if len(words) != len(pattern) {
		return false
	}

	p2w := make(map[byte]string)
	w2p := make(map[string]byte)

	for i := 0; i < len(words); i++ {
		ch := pattern[i]
		word := words[i]

		map_word, ok_word := p2w[ch]
		map_ch, ok_ch := w2p[word]

		if ok_word || ok_ch {
			if !ok_word || !ok_ch {
				return false
			}
			if map_word != word ||
				map_ch != ch {
				return false
			}
			continue
		}

		p2w[ch] = word
		w2p[word] = ch
	}

	return true
}
