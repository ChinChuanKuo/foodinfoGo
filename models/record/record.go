package record

import (
	"fmt"
	"foodinfoGo/appcode"
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

func SearchRecord(formId string, pages string, inoper string) bool {
	o := orm.NewOrm()
	var mainRows []orm.Params
	cordCall := []interface{}{inoper}
	results, _ := o.Raw("call foodinfo.searchrecordlog(?)", cordCall).Values(&mainRows)
	datetime := appcode.GetDateTime()
	if results == 0 {
		cordExec := []interface{}{formId, pages, strings.Split(datetime, " ")[0], strings.Split(datetime, " ")[1], inoper}
		_, err := o.Raw("insert into foodinfo.recordlog (formId,pages,stdate,sttime,inoper) values (?, ?, ?, ?, ?)", cordExec).Exec()
		if err == nil {
			return false
		}
	}
	if mainRows[0]["formId"] != formId || mainRows[0]["pages"] != pages {
		if mainRows[0]["endate"] == "" && mainRows[0]["entime"] == "" {
			cordExec := []interface{}{strings.Split(datetime, " ")[0], strings.Split(datetime, " ")[1], formId, pages, inoper}
			_, err := o.Raw("update foodinfo.recordlog set endate = ?,entime = ? where formId = ? and pages = ? and inoper = ?", cordExec).Exec()
			if err != nil {
				return false
			}
		}
		cordExec := []interface{}{formId, pages, strings.Split(datetime, " ")[0], strings.Split(datetime, " ")[1], inoper}
		_, err := o.Raw("insert into foodinfo.recordlog (formId,pages,stdate,sttime,inoper) values (?, ?, ?, ?, ?)", cordExec).Exec()
		if err != nil {
			return false
		}
	}
	return true
}
