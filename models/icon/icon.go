package icon

import (
	"fmt"
	"foodinfoGo/appcode"
	"foodinfoGo/models"

	"github.com/astaxie/beego/orm"
)

func init() {
	database := appcode.GetDataBase()
	orm.RegisterDriver("mysql", orm.DRMySQL)
	orm.RegisterDataBase("default", database.Kuopt.Sqlserver, database.Kuopt.Datastring)
	fmt.Println("Successfully Connect foodinfo database")
}

func GetSearchModels(userData models.UserData) *models.StatusModels {
	/*o := orm.NewOrm()
	var itemRows []orm.Params
	loadCall := []interface{}{userData.Userid}
	results, _ := o.Raw("select value,icon from foodinfo.qaitemform where inoper = ?;", loadCall).Values(&itemRows)
	if results == 0 {
		return &models.StatusModels{Status: "nodata"}
	}*/
	return &models.StatusModels{Status: "istrue"}
}

func GetInsertModels(iIconData models.IIconData) *models.StatusModels {
	o := orm.NewOrm()
	for _, items := range iIconData.Items {
		var itemRows []orm.Params
		saveCall := []interface{}{items["value"]}
		results, _ := o.Raw("select value,icon from foodinfo.iconform where value = ?;", saveCall).Values(&itemRows)
		if results == 0 {
			saveExec := []interface{}{items["value"], items["icon"], iIconData.Newid}
			_, err := o.Raw("insert into foodinfo.iconform (value,icon,inoper) values (?, ?, ?)", saveExec).Exec()
			if err != nil {
				return &models.StatusModels{Status: "error"}
			}
		}
	}
	for _, qaitems := range iIconData.Qaitems {
		var itemRows []orm.Params
		saveCall := []interface{}{"0", qaitems["value"]}
		results, _ := o.Raw("select value,icon from foodinfo.itemform where padding = ? and value = ?;", saveCall).Values(&itemRows)
		if results == 0 {
			saveExec := []interface{}{"0", qaitems["value"], qaitems["icon"], iIconData.Newid}
			_, err := o.Raw("insert into foodinfo.itemform (padding,value,icon,inoper) values (?, ?, ?, ?)", saveExec).Exec()
			if err != nil {
				return &models.StatusModels{Status: "error"}
			}
		}
	}
	return &models.StatusModels{Status: "saveSuccess"}
}
