package appcode

import (
	"fmt"
	"strings"
	"time"
)

func GetDateTime() string {
	return fmt.Sprintf(time.Now().Format("2006-01-02 15:04:05"))
}

func GetDaysOrHours(stDateTime, edDateTime string) string {
	start, err := time.Parse("2006-01-02 15:04:05", stDateTime)
	end, err := time.Parse("2006-01-02 15:04:05", edDateTime)
	if err == nil && start.Before(end) {
		differHours := end.Sub(start).Hours()
		if differHours > 24 {
			return strings.Split(fmt.Sprintf("%f", differHours/24), ".")[0] + "天前"
		}
		if differHours > 1 {
			return strings.Split(fmt.Sprintf("%f", differHours), ".")[0] + "小時前"
		}
		return strings.Split(fmt.Sprintf("%f", differHours*60), ".")[0] + "分鐘前"
	}
	return "0分鐘前"
}

func ComparsionBeforeMinutes(stDateTime, edDateTime string, minutes int) bool {
	start, err := time.Parse("2006-01-02 15:04:05", stDateTime)
	end, err := time.Parse("2006-01-02 15:04:05", edDateTime)
	endadd := end.Add(time.Minute * time.Duration(minutes))
	if err == nil && start.Before(endadd) {
		return true
	}
	return false
}

func ComparsionAfterDate(startDate, endDate string) bool {
	start, err := time.Parse("2006-01-02", startDate)
	end, err := time.Parse("2006-01-02", endDate)
	if err == nil && start.After(end) {
		return true
	}
	return false
}
