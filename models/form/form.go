package form

import (
	"fmt"
	"foodinfoGo/appcode"
	"foodinfoGo/models"
	"time"

	"github.com/astaxie/beego/orm"
	_ "github.com/go-sql-driver/mysql"
)

func init() {
	database := appcode.GetDataBase()
	orm.RegisterDriver("mysql", orm.DRMySQL)
	orm.RegisterDataBase("default", database.Kuopt.Sqlserver, database.Kuopt.Datastring)
	fmt.Println("Successfully Connect foodinfo database")
}

func GetCheckNewModels(userData models.UserData) *models.StatusModels {
	o := orm.NewOrm()
	var checkRows []orm.Params
	checkCall := []interface{}{userData.Userid, "1"}
	results, _ := o.Raw("call foodinfo.checkformnewid(?, ?)", checkCall).Values(&checkRows)
	if results == 0 {
		return &models.StatusModels{Status: "nodata"}
	}
	if checkRows[0]["isused"] == "1" {
		return &models.StatusModels{Status: "istrue"}
	}
	return &models.StatusModels{Status: "islock"}
}

func GetLoginFormModels(userData models.UserData, userAgent string) *models.LoginModels {
	o := orm.NewOrm()
	var loginRows []orm.Params
	infolist := appcode.GetInfoObject()
	loginCall := []interface{}{userData.Userid, infolist.ExternIp, "1"}
	results, _ := o.Raw("call foodinfo.checkformlogin(?, ?, ?)", loginCall).Values(&loginRows)
	if results == 0 {
		return &models.LoginModels{Status: "nodata"}
	}
	if loginRows[0]["isused"] == "1" && loginRows[0]["islogin"] == "1" {
		loginExec := []interface{}{infolist.CPU, infolist.InternIp, infolist.Hostname, appcode.GetBrowser(userAgent), infolist.OS, loginRows[0]["newid"], infolist.ExternIp, "1"}
		_, err := o.Raw("update foodinfo.sitelog set cpu = ?,internip = ?,hostname = ?,browser = ?,os = ? where newid = ? and externip = ? and islogin = ?", loginExec).Exec()
		if err == nil {
			return &models.LoginModels{Newid: loginRows[0]["newid"].(string), Name: appcode.Substring(loginRows[0]["username"].(string), 0, 1), Allname: loginRows[0]["username"].(string), Status: "istrue"}
		}
		return &models.LoginModels{Status: "error"}
	}
	return &models.LoginModels{Status: "islock"}
}

func GetBadgeFormModels(otherData models.OtherData) *models.StatusModels {
	o := orm.NewOrm()
	isbreak := true
	badge := "0"
	for isbreak {
		time.Sleep(time.Duration(5) * time.Second)
		var mainRows []orm.Params
		loadCall := []interface{}{otherData.Userid, "0"}
		_, err := o.Raw("call foodinfo.countnoticeform(?, ?)", loadCall).Values(&mainRows)
		if err != nil {
			isbreak = false
		}
		badge = mainRows[0]["counts"].(string)
		if badge != otherData.Values {
			isbreak = false
		}
	}
	return &models.StatusModels{Status: badge}
}

func GetPermissModels(UserData models.UserData) *models.PermissModels {
	o := orm.NewOrm()
	var mainRows []orm.Params
	loadCall := []interface{}{UserData.Userid}
	results, _ := o.Raw("select p.issearch,p.isinsert,p.ismodify,p.isdelete,p.isexport from foodinfo.siteber as s inner join foodinfo.permission as p on s.permissajax = p.permissajax where s.newid = ?;", loadCall).Values(&mainRows)
	if results == 0 {
		return &models.PermissModels{Insert: false, Update: false, Delete: false, Export: false}
	}
	return &models.PermissModels{Insert: mainRows[0]["isinsert"] == "1", Update: mainRows[0]["ismodify-"] == "1", Delete: mainRows[0]["isdelete"] == "1", Export: mainRows[0]["isexport"] == "1"}
}

func GetRecordModels(userData models.UserData) *models.ItemsModels {
	o := orm.NewOrm()
	var mainRows []orm.Params
	loadCall := []interface{}{userData.Userid}
	results, _ := o.Raw("call foodinfo.searchrecordform(?);", loadCall).Values(&mainRows)
	if results == 0 {
		return &models.ItemsModels{Showitem: false}
	}
	items := []map[string]interface{}{}
	for _, main := range mainRows {
		items = append(items, map[string]interface{}{"link": main["link"], "icon": main["icon"], "value": main["value"]})
	}
	return &models.ItemsModels{Showitem: true, Items: items}
}

func GetBadgeModels(userData models.UserData) *models.ItemsModels {
	o := orm.NewOrm()
	/*loadExec := []interface{}{"1", userData.Userid, userData.Userid, "0"}
	_, err := o.Raw("update foodinfo.noticeform set status = ?,mooper = ? where newid = ? and status = ?", loadExec).Exec()
	if err != nil {
		return &models.ItemsModels{Showitem: false}
	}
	var mainRows []orm.Params
	loadCall := []interface{}{userData.Userid}
	results, _ := o.Raw("call foodinfo.searchnoticeform(?);", loadCall).Values(&mainRows)
	if results == 0 {
		return &models.ItemsModels{Showitem: false}
	}
	datetime := appcode.GetDateTime()
	items := []map[string]interface{}{}
	for _, main := range mainRows {
		items = append(items, map[string]interface{}{"link": main["link"], "name": appcode.Substring(main["username"].(string), 0, 1), "value": main["value"], "datetime": appcode.GetDaysOrHours(main["indate"].(string)+" "+main["intime"].(string), datetime)})
	}*/
	var mainRows []orm.Params
	loadCall := []interface{}{userData.Userid}
	results, _ := o.Raw("call foodinfo.searchnoticeform(?);", loadCall).Values(&mainRows)
	if results == 0 {
		return &models.ItemsModels{Showitem: false}
	}
	datetime := appcode.GetDateTime()
	items := []map[string]interface{}{}
	for _, main := range mainRows {
		items = append(items, map[string]interface{}{"link": main["link"], "name": appcode.Substring(main["username"].(string), 0, 1), "value": main["value"], "datetime": appcode.GetDaysOrHours(main["indate"].(string)+" "+main["intime"].(string), datetime)})
	}
	return &models.ItemsModels{Showitem: true, Items: items}
}
