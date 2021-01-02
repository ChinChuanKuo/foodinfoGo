package files

import (
	"fmt"
	"foodinfoGo/appcode"
	"foodinfoGo/models"
	"io"
	"io/ioutil"
	"net/http"
	"os"
	"strings"

	"github.com/astaxie/beego/orm"
	_ "github.com/go-sql-driver/mysql"
)

func init() {
	database := appcode.GetDataBase()
	orm.RegisterDriver("mysql", orm.DRMySQL)
	orm.RegisterDataBase("default", database.Kuopt.Sqlserver, database.Kuopt.Datastring)
	fmt.Println("Successfully Connect foodinfo database")
}

func GetUploadModels(filePath, filename string) *models.SFileModels {
	o := orm.NewOrm()
	var moduleRows []orm.Params
	loadCall := []interface{}{appcode.Substring(filename, strings.LastIndex(filename, ".")+1, len(filename)), "1"}
	results, _ := o.Raw("call foodinfo.searchfimoduleinfo(?, ?)", loadCall).Values(&moduleRows)
	if results == 0 {
		return &models.SFileModels{Status: "failed"}
	}
	if moduleRows[0]["imaged"] == "0" && moduleRows[0]["videoed"] == "0" && moduleRows[0]["audioed"] == "0" {
		return &models.SFileModels{Status: "failed"}
	}
	bytes, err := ioutil.ReadFile(filePath + filename)
	if err != nil {
		return &models.SFileModels{Status: "failed"}
	}
	return &models.SFileModels{File: bytes, Status: "istrue"}
}

func GetWebsiteModels(sRowsData models.SRowsData, filePath string) *models.SFileModels {
	resp, err := http.Get(sRowsData.Value)
	if err != nil {
		return &models.SFileModels{Status: "failed"}
	}
	defer resp.Body.Close()
	filename := "logo.svg"
	out, err := os.Create(filePath + filename)
	if err != nil {
		return &models.SFileModels{Status: "failed"}
	}
	defer out.Close()
	_, err = io.Copy(out, resp.Body)
	if err != nil {
		return &models.SFileModels{Status: "failed"}
	}
	bytes, err := ioutil.ReadFile(filePath + filename)
	if err != nil {
		return &models.SFileModels{Status: "failed"}
	}
	return &models.SFileModels{File: bytes, Status: "istrue"}
}
