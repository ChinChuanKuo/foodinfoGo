package appcode

import (
	"encoding/json"
	"os"
)

type Database struct {
	Kuopt struct {
		Sqlserver  string `json:"sqlserver"`
		Datastring string `json:"datastring"`
	}
}

func GetDataBase() Database {
	var database Database
	jsonFile, _ := os.Open("/users/chinchuankuo/documents/reactGo.json")
	defer jsonFile.Close()
	jsonParser := json.NewDecoder(jsonFile)
	jsonParser.Decode(&database)
	return database
}
