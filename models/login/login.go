package login

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

func GetUserModels(userData models.UserData) *models.UserModels {
	if userData.Userid == "" {
		return &models.UserModels{Status: "errorUserid"}
	}
	o := orm.NewOrm()
	var userRows []orm.Params
	userCall := []interface{}{userData.Userid, "1"}
	results, _ := o.Raw("call foodinfo.checksiteber(?, ?)", userCall).Values(&userRows)
	if results == 0 {
		return &models.UserModels{Status: "nodata"}
	}
	if userRows[0]["isused"] == "1" {
		return &models.UserModels{Newid: userRows[0]["newid"].(string), Status: "istrue"}
	}
	return &models.UserModels{Status: "islock"}
}

func GetLoginModels(loginData models.LoginData, userAgent string) *models.LoginModels {
	if loginData.Userid == "" {
		return &models.LoginModels{Status: "errorUserid"}
	}
	if loginData.Password == "" {
		return &models.LoginModels{Status: "errorPassword"}
	}
	o := orm.NewOrm()
	var loginRows []orm.Params
	password := appcode.GetEncry256(loginData.Password)
	loginCall := []interface{}{loginData.Userid, password, "1"}
	results, _ := o.Raw("call foodinfo.loginsiteber(?, ?, ?)", loginCall).Values(&loginRows)
	if results == 0 {
		return &models.LoginModels{Status: "nodata"}
	}
	if loginRows[0]["isused"] == "1" {
		var checkRows []orm.Params
		infolist := appcode.GetInfoObject()
		loginCall := []interface{}{loginData.Userid, password, infolist.ExternIp, "1"}
		results, _ := o.Raw("call foodinfo.checksitelog(?, ?, ?, ?)", loginCall).Values(&checkRows)
		if results == 0 {
			loginExec := []interface{}{loginRows[0]["newid"], infolist.ExternIp, loginData.Longitude, loginData.Latitude, "", "", infolist.CPU, infolist.InternIp, infolist.Hostname, appcode.GetBrowser(userAgent), infolist.OS, "1"}
			_, err := o.Raw("insert into foodinfo.sitelog (newid,externip,longitude,latitude,country,city,cpu,internip,hostname,browser,os,islogin) values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", loginExec).Exec()
			if err == nil {
				return &models.LoginModels{Newid: loginRows[0]["newid"].(string), Name: appcode.Substring(loginRows[0]["username"].(string), 0, 1), Allname: loginRows[0]["username"].(string), Status: "istrue"}
			}
			return &models.LoginModels{Status: "error"}
		}
		if checkRows[0]["isused"] == "1" && checkRows[0]["islogin"] == "1" {
			loginExec := []interface{}{loginData.Longitude, loginData.Latitude, infolist.CPU, infolist.InternIp, infolist.Hostname, appcode.GetBrowser(userAgent), infolist.OS, checkRows[0]["newid"], infolist.ExternIp, "1"}
			_, err := o.Raw("update foodinfo.sitelog set longitude = ?,latitude = ?,cpu = ?,internip = ?,hostname = ?,browser = ?,os = ? where newid = ? and externip = ? and islogin = ?", loginExec).Exec()
			if err == nil {
				return &models.LoginModels{Newid: checkRows[0]["newid"].(string), Name: appcode.Substring(checkRows[0]["username"].(string), 0, 1), Allname: checkRows[0]["username"].(string), Status: "istrue"}
			}
			return &models.LoginModels{Status: "error"}
		}
	}
	return &models.LoginModels{Status: "islock"}
}
