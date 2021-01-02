package appcode

import (
	"fmt"
	"math"
)

func GetDistance(longitude1, longitude2, latitude1, latitude2 float64) float64 {
	radlatitude1 := GetRad(latitude1)
	radlatitude2 := GetRad(latitude2)
	a := radlatitude1 - radlatitude2
	b := GetRad(longitude1) - GetRad(longitude2)
	return 2 * math.Asin(math.Sqrt(math.Pow(math.Sin(a/2), 2)+math.Cos(radlatitude1)*math.Cos(radlatitude2)*math.Pow(math.Sin(b/2), 2))) * 6378.137
}

func GetDistanceUnit(distance float64) string {
	if distance > 1 {
		return fmt.Sprintf("%.2f", GetRound(distance, 0.05)) + "公里"
	}
	return fmt.Sprintf("%.2f", math.Floor(distance*1000)) + "公尺"
}
