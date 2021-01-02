package forget

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

func GetForgetUserModels(otherData models.OtherData) *models.StatusModels {
	if otherData.Userid == "" {
		return &models.StatusModels{Status: "nousers"}
	}
	if otherData.Values == "" {
		return &models.StatusModels{Status: "errorForget"}
	}
	o := orm.NewOrm()
	var forgetRows []orm.Params
	forgetCall := []interface{}{otherData.Userid, otherData.Values, "1"}
	results, _ := o.Raw("call foodinfo.forgetsiteber(?, ?, ?)", forgetCall).Values(&forgetRows)
	if results == 0 {
		return &models.StatusModels{Status: "nodata"}
	}
	if forgetRows[0]["isused"] == "0" {
		return &models.StatusModels{Status: "islock"}
	}
	datetime := appcode.GetDateTime()
	forgetExec := []interface{}{strings.Split(datetime, " ")[0], strings.Split(datetime, " ")[1], strconv.Itoa(appcode.GetRandom(100000, 999999)), otherData.Userid}
	_, err := o.Raw("update foodinfo.siteber set vedate = ?,vetime = ?,vecode = ? where newid = ?", forgetExec).Exec()
	if err == nil {
		return &models.StatusModels{Status: "istrue"}
	}
	return &models.StatusModels{Status: "error"}
}
