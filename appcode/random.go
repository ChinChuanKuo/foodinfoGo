package appcode

import "math/rand"

func GetRandom(min, max int) int {
	return min + rand.Intn(max-min)
}
