package appcode

import "fmt"

func Substring(source string, start int, end int) string {
	value := []rune(source)
	if start > end || end > len(value) {
		return source
	}
	return string(value[start:end])
}

func Padleftstring(total string, source string) string {
	return fmt.Sprintf("%0"+total+"s", source)
}

func Chkarraystring(outValue string, checked bool, tile string, value string) string {
	if checked && value == "" {
		if outValue == "radio" || outValue == "checkbox" {
			return "sorry, " + tile + " column is not select option yet"
		}
		return "sorry, " + tile + " column is not writen yet"
	}
	return ""
}
