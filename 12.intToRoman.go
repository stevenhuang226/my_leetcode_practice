package main

func intToRoman(num int) string {
	romanTable := [][]string{
		{"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
		{"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
		{"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
		{"", "M", "MM", "MMM"},
	}

	result := ""

	thousands := num / 1000
	hundreds := (num / 100) % 10
	tens := (num / 10) % 10
	ones := num % 10

	result += romanTable[3][thousands]
	result += romanTable[2][hundreds]
	result += romanTable[1][tens]
	result += romanTable[0][ones]

	return result
}
