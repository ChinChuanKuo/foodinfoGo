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
		var iconRows []orm.Params
		saveCall := []interface{}{items["value"], items["icon"], iIconData.Newid}
		_, err := o.Raw("call foodinfo.checkiconform(?, ?, ?)", saveCall).Values(&iconRows)
		if err != nil {
			return &models.StatusModels{Status: "error"}
		}
	}
	for _, qaitems := range iIconData.Qaitems {
		var itemRows []orm.Params
		saveCall := []interface{}{qaitems["value"], "0", qaitems["icon"], iIconData.Newid}
		_, err := o.Raw("call foodinfo.checkitemform(?, ?, ?, ?)", saveCall).Values(&itemRows)
		if err != nil {
			return &models.StatusModels{Status: "error"}
		}
	}
	return &models.StatusModels{Status: "saveSuccess"}
}
