package signup

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

func GetSignupUserModels(signupData models.SignupData) *models.StatusModels {
	if signupData.Userid == "" {
		return &models.StatusModels{Status: "errorEmail"}
	}
	if signupData.Password == "" {
		return &models.StatusModels{Status: "errorPassword"}
	}
	if signupData.Username == "" {
		return &models.StatusModels{Status: "errorUsername"}
	}
	if signupData.Birthday == "" {
		return &models.StatusModels{Status: "errorBirthday"}
	}
	o := orm.NewOrm()
	var signupRows []orm.Params
	signupCall := []interface{}{signupData.Userid}
	results, _ := o.Raw("select newid,userid from foodinfo.siteber where email = ?;", signupCall).Values(&signupRows)
	if results == 0 {
		password := appcode.GetEncry256(signupData.Password)
		signupExec := []interface{}{signupData.Userid, password, signupData.Username, signupData.Birthday, "general"}
		_, err := o.Raw("insert into foodinfo.siteber (email,password,username,birthday,permissajax) values (?, ?, ?, ?, ?)", signupExec).Exec()
		if err == nil {
			return &models.StatusModels{Status: "istrue"}
		}
		return &models.StatusModels{Status: "error"}
	}
	return &models.StatusModels{Status: "error"}
}
