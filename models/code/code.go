package code

import (
	"fmt"
	"foodinfoGo/appcode"
	"foodinfoGo/models"
	"strconv"
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

func GetCodeUserModels(otherData models.OtherData) *models.StatusModels {
	if otherData.Userid == "" {
		return &models.StatusModels{Status: "nousers"}
	}
	if otherData.Values == "" {
		return &models.StatusModels{Status: "errorCode"}
	}
	o := orm.NewOrm()
	var codeRows []orm.Params
	codeCall := []interface{}{otherData.Userid, otherData.Values, "1"}
	results, _ := o.Raw("call foodinfo.codesiteber(?, ?, ?)", codeCall).Values(&codeRows)
	if results == 0 {
		return &models.StatusModels{Status: "nodata"}
	}
	if codeRows[0]["isused"] == "0" {
		return &models.StatusModels{Status: "islock"}
	}
	datetime := appcode.GetDateTime()
	if appcode.ComparsionBeforeMinutes(datetime, codeRows[0]["vedate"].(string)+" "+codeRows[0]["vetime"].(string), 10) {
		codeExec := []interface{}{"", "", "", otherData.Userid}
		_, err := o.Raw("update foodinfo.siteber set vedate = ?,vetime = ?,vecode = ? where newid = ?", codeExec).Exec()
		if err == nil {
			return &models.StatusModels{Status: "istrue"}
		}
		return &models.StatusModels{Status: "error"}
	}
	codeExec := []interface{}{strings.Split(datetime, " ")[0], strings.Split(datetime, " ")[1], strconv.Itoa(appcode.GetRandom(100000, 999999)), otherData.Userid}
	_, err := o.Raw("update foodinfo.siteber set vedate = ?,vetime = ?,vecode = ? where newid = ?", codeExec).Exec()
	if err == nil {
		return &models.StatusModels{Status: "resend"}
	}
	return &models.StatusModels{Status: "error"}
}
