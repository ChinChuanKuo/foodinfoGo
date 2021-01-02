package fesdate

import (
	"fmt"
	"foodinfoGo/appcode"
	"foodinfoGo/models"
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

func GetSearchModels(dFormData models.DFormData) *models.SInfoModels {
	if len(strings.TrimSpace(dFormData.Formid)) == 0 {
		return &models.SInfoModels{Status: "errorSearch"}
	}
	o := orm.NewOrm()
	var moduleRows []orm.Params
	loadCall := []interface{}{}
	results, _ := o.Raw("call foodinfo.searchstmoduleinfo", loadCall).Values(&moduleRows)
	if results == 0 {
		return &models.SInfoModels{Status: "nodata"}
	}
	var mainRows []orm.Params
	loadCall = []interface{}{dFormData.Formid, dFormData.Newid}
	results, _ = o.Raw("call foodinfo.searchstoreform(?, ?)", loadCall).Values(&mainRows)
	if results == 0 {
		return &models.SInfoModels{Status: "nodata"}
	}
	var festRows []orm.Params
	loadCall = []interface{}{}
	results, _ = o.Raw("call foodinfo.searchfemoduleinfo", loadCall).Values(&festRows)
	if results == 0 {
		return &models.SInfoModels{Status: "nodata"}
	}
	heads := []string{}
	for _, fest := range festRows {
		heads = append(heads, fest["tile"].(string))
	}
	var feitemRows []orm.Params
	loadCall = []interface{}{dFormData.Formid, dFormData.Newid}
	results, _ = o.Raw("call foodinfo.searchfestform(?, ?)", loadCall).Values(&feitemRows)
	items := []map[string]interface{}{}
	for _, feitem := range feitemRows {
		festitems := []map[string]interface{}{}
		if festRows[0]["outValue"] == "radio" || festRows[0]["outValue"] == "checkbox" || festRows[0]["outValue"] == "droplist" {
			var optionRows []orm.Params
			loadCall = []interface{}{festRows[0]["feId"]}
			results, _ = o.Raw("call foodinfo.searchfeoptionform(?)", loadCall).Values(&optionRows)
			for _, option := range optionRows {
				festitems = append(festitems, map[string]interface{}{"optionPadding": false, "value": option["value"]})
			}
		}
		dateitems := []map[string]interface{}{}
		if festRows[1]["outValue"] == "radio" || festRows[1]["outValue"] == "checkbox" || festRows[1]["outValue"] == "droplist" {
			var optionRows []orm.Params
			loadCall = []interface{}{festRows[1]["feId"]}
			results, _ = o.Raw("call foodinfo.searchfeoptionform(?)", loadCall).Values(&optionRows)
			for _, option := range optionRows {
				dateitems = append(dateitems, map[string]interface{}{"optionPadding": false, "value": option["value"]})
			}
		}
		sttimeitems := []map[string]interface{}{}
		if festRows[2]["outValue"] == "radio" || festRows[2]["outValue"] == "checkbox" || festRows[2]["outValue"] == "droplist" {
			var optionRows []orm.Params
			loadCall = []interface{}{festRows[2]["feId"]}
			results, _ = o.Raw("call foodinfo.searchfeoptionform(?)", loadCall).Values(&optionRows)
			for _, option := range optionRows {
				sttimeitems = append(sttimeitems, map[string]interface{}{"optionPadding": false, "value": option["value"]})
			}
		}
		entimeitems := []map[string]interface{}{}
		if festRows[3]["outValue"] == "radio" || festRows[3]["outValue"] == "checkbox" || festRows[3]["outValue"] == "droplist" {
			var optionRows []orm.Params
			loadCall = []interface{}{festRows[3]["feId"]}
			results, _ = o.Raw("call foodinfo.searchfeoptionform(?)", loadCall).Values(&optionRows)
			for _, option := range optionRows {
				entimeitems = append(entimeitems, map[string]interface{}{"optionPadding": false, "value": option["value"]})
			}
		}
		items = append(items, map[string]interface{}{"daId": feitem["daId"], "festId": festRows[0]["feId"], "showFest": true, "festOutValue": festRows[0]["outValue"], "festChecked": festRows[0]["checked"] == "1", "showFestDrop": false, "showFestFile": feitem["fest"] != "", "festValue": feitem["fest"], "showFestMenu": false, "festitems": festitems, "dateId": festRows[1]["feId"], "showDate": true, "dateOutValue": festRows[1]["outValue"], "dateChecked": festRows[1]["checked"] == "1", "showDateDrop": false, "showDateFile": feitem["date"] != "", "dateValue": feitem["date"], "showDateMenu": false, "dateitems": dateitems, "sttimeId": festRows[2]["feId"], "showSttime": true, "sttimeOutValue": festRows[2]["outValue"], "sttimeChecked": festRows[2]["checked"] == "1", "showSttimeDrop": false, "showSttimeFile": feitem["sttime"] != "", "sttimeValue": feitem["sttime"], "showSttimeMenu": false, "sttimeitems": sttimeitems, "entimeId": festRows[3]["feId"], "showEntime": true, "entimeOutValue": festRows[3]["outValue"], "entimeChecked": festRows[3]["checked"] == "1", "showEntimeDrop": false, "showEntimeFile": feitem["entime"] != "", "entimeValue": feitem["entime"], "showEntimeMenu": false, "entimeitems": entimeitems, "showEnter": false, "showModify": false})
	}
	return &models.SInfoModels{Formid: mainRows[0]["formId"].(string), Tile: mainRows[0]["tile"].(string), Desc: mainRows[0]["desc"].(string), Checked: mainRows[0]["status"] == "1", Heads: heads, Items: items, Status: "istrue"}
}

func GetInsertModels(iFormData models.IFormData) *models.StatusModels {
	for _, items := range iFormData.Items {
		if items["showDelete"] == false {
			wrong := appcode.Chkarraystring(items["festOutValue"].(string), items["festChecked"].(bool), items["daId"].(string), items["festValue"].(string))
			if wrong != "" {
				return &models.StatusModels{Status: wrong}
			}
			wrong = appcode.Chkarraystring(items["dateOutValue"].(string), items["dateChecked"].(bool), items["daId"].(string), items["dateValue"].(string))
			if wrong != "" {
				return &models.StatusModels{Status: wrong}
			}
			wrong = appcode.Chkarraystring(items["sttimeOutValue"].(string), items["sttimeChecked"].(bool), items["daId"].(string), items["sttimeValue"].(string))
			if wrong != "" {
				return &models.StatusModels{Status: wrong}
			}
			wrong = appcode.Chkarraystring(items["entimeOutValue"].(string), items["entimeChecked"].(bool), items["daId"].(string), items["entimeValue"].(string))
			if wrong != "" {
				return &models.StatusModels{Status: wrong}
			}
		}
	}
	o := orm.NewOrm()
	var mainRows []orm.Params
	saveCall := []interface{}{iFormData.Formid, iFormData.Newid}
	results, _ := o.Raw("call foodinfo.searchstoreform(?, ?)", saveCall).Values(&mainRows)
	if results == 0 {
		return &models.StatusModels{Status: "nodata"}
	}
	tile := "noTitle"
	if iFormData.Tile != "" {
		tile = iFormData.Tile
	}
	if mainRows[0]["tile"] != tile || mainRows[0]["desc"] != iFormData.Desc {
		saveExec := []interface{}{tile, iFormData.Desc, iFormData.Newid, iFormData.Formid, iFormData.Newid}
		_, err := o.Raw("update foodinfo.stmainform set tile = ?,`desc` = ?,mooper = ? where formId = ? and inoper = ?", saveExec).Exec()
		if err != nil {
			return &models.StatusModels{Status: "error"}
		}
	}
	for _, items := range iFormData.Items {
		saveExec := []interface{}{items["sttimeValue"], items["entimeValue"], iFormData.Newid, iFormData.Formid, items["daId"], iFormData.Newid}
		_, err := o.Raw("update foodinfo.stfestform set sttime = ?,entime = ?,mooper = ? where formId = ? and daId = ? and inoper = ?", saveExec).Exec()
		if err != nil {
			return &models.StatusModels{Status: "error"}
		}
	}
	return &models.StatusModels{Status: "istrue"}
}
