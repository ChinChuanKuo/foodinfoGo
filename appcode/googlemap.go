package appcode

import (
	"encoding/json"
	"fmt"
	"net/http"
	"os"
	"strconv"
)

func GetLocation(address string) []string {
	resp, err := http.Get("https://maps.googleapis.com/maps/api/geocode/json?address=" + address + "&key=" + os.Getenv("GOOGLE_MAP_API"))
	if err == nil {
		defer resp.Body.Close()
		result := make(map[string]interface{})
		json.NewDecoder(resp.Body).Decode(&result)
		if result["status"] == "OK" {
			location := result["results"].([]interface{})[0].(map[string]interface{})["geometry"].(map[string]interface{})["location"]
			return []string{strconv.FormatFloat(location.(map[string]interface{})["lng"].(float64), 'f', 6, 64), strconv.FormatFloat(location.(map[string]interface{})["lat"].(float64), 'f', 6, 64)}
		}
	}
	return []string{"", ""}
}

func GetDirections(mode, language string, longitude1, longitude2, latitude1, latitude2 float64) string {
	resp, err := http.Get("https://maps.googleapis.com/maps/api/directions/json?mode=" + mode + "&language=" + language + "&origin=" + fmt.Sprintf("%f", latitude1) + "," + fmt.Sprintf("%f", longitude1) + "&destination=" + fmt.Sprintf("%f", latitude2) + "," + fmt.Sprintf("%f", longitude2) + "&key=AIzaSyCCb9Rt1ANXKbxEyB92TDlfqiVjSNjLyQM")
	if err == nil {
		defer resp.Body.Close()
		result := make(map[string]interface{})
		json.NewDecoder(resp.Body).Decode(&result)
		if result["status"] == "OK" {
			return result["routes"].([]interface{})[0].(map[string]interface{})["legs"].([]interface{})[0].(map[string]interface{})["steps"].([]interface{})[0].(map[string]interface{})["html_instructions"].(string)
		}
	}
	return ""
}

func GetDistanceMatrix(mode, language string, longitude1, longitude2, latitude1, latitude2 float64) []string {
	resp, err := http.Get("https://maps.googleapis.com/maps/api/distancematrix/json?mode=" + mode + "&language=" + language + "&origins=" + fmt.Sprintf("%f", latitude1) + "," + fmt.Sprintf("%f", longitude1) + "&destinations=" + fmt.Sprintf("%f", latitude2) + "," + fmt.Sprintf("%f", longitude2) + "&key=AIzaSyCCb9Rt1ANXKbxEyB92TDlfqiVjSNjLyQM")
	if err == nil {
		defer resp.Body.Close()
		result := make(map[string]interface{})
		json.NewDecoder(resp.Body).Decode(&result)
		if result["status"] == "OK" {
			elements := result["rows"].([]interface{})[0].(map[string]interface{})["elements"].([]interface{})[0]
			return []string{elements.(map[string]interface{})["duration"].(map[string]interface{})["text"].(string), elements.(map[string]interface{})["distance"].(map[string]interface{})["text"].(string)}
		}
	}
	return []string{"", ""}
}
