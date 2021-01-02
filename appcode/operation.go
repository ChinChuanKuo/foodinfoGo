package appcode

import "math"

func GetRad(d float64) float64 {
	return d * math.Pi / 180.0
}

func GetRound(x, unit float64) float64 {
	return math.Round(x/unit) * unit
}
