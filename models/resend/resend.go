package resend

import (
	"fmt"
	"foodinfoGo/appcode"
	"foodinfoGo/models"

	"github.com/astaxie/beego/orm"
	_ "github.com/go-sql-driver/mysql"
)

func init() {
	database := appcode.GetDataBase()
	orm.RegisterDriver("mysql", orm.DRMySQL)
	orm.RegisterDataBase("default", database.Kuopt.Sqlserver, database.Kuopt.Datastring)
	fmt.Println("Successfully Connect foodinfo database")
}

func GetResendUserModels(otherData models.OtherData) *models.StatusModels {
	if otherData.Userid == "" {
		return &models.StatusModels{Status: "nousers"}
	}
	if otherData.Values == "" {
		return &models.StatusModels{Status: "errorResend"}
	}
	o := orm.NewOrm()
	var resendRows []orm.Params
	resendCall := []interface{}{otherData.Userid, "1"}
	results, _ := o.Raw("call foodinfo.resendsiteber(?, ?)", resendCall).Values(&resendRows)
	if results == 0 {
		return &models.StatusModels{Status: "nodata"}
	}
	if resendRows[0]["isused"] == "0" {
		return &models.StatusModels{Status: "islock"}
	}
	password := appcode.GetEncry256(otherData.Values)
	resendExec := []interface{}{password, otherData.Userid}
	_, err := o.Raw("update foodinfo.siteber set password = ? where newid = ?", resendExec).Exec()
	if err == nil {
		return &models.StatusModels{Status: "istrue"}
	}
	return &models.StatusModels{Status: "error"}
}
