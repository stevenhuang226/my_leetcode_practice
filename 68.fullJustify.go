package main

func fullJustify(words []string, maxWidth int) []string {
	var result []string

	for i := 0; i < len(words); {
		lineStart := i
		lineLen := 0

		for i < len(words) {
			wordLen := len(words[i])
			if lineLen+wordLen+(i-lineStart) > maxWidth {
				break
			}
			lineLen += wordLen
			i++
		}

		lineEnd := i
		wordCount := lineEnd - lineStart

		if wordCount == 1 || lineEnd == len(words) {
			line := words[lineStart]
			for i2 := 1; i2 < wordCount; i2++ {
				line += " "
				line += words[lineStart+i2]
			}
			for len(line) < maxWidth {
				line += " "
			}
			result = append(result, line)
			continue
		}

		spaceCount := maxWidth - lineLen
		gapCount := wordCount - 1
		baseSpace := spaceCount / gapCount
		extraLeft := spaceCount % gapCount

		line := ""
		for i2 := 0; i2 < gapCount; i2++ {
			line += words[lineStart+i2]
			spaces := baseSpace
			if i2 < extraLeft {
				spaces++
			}
			for i3 := 0; i3 < spaces; i3++ {
				line += " "
			}
		}
		line += words[lineEnd-1]

		result = append(result, line)
	}

	return result
}
