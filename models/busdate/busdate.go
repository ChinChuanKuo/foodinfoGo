package busdate

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
	var weekRows []orm.Params
	loadCall = []interface{}{}
	results, _ = o.Raw("call foodinfo.searchwkmoduleinfo", loadCall).Values(&weekRows)
	if results == 0 {
		return &models.SInfoModels{Status: "nodata"}
	}
	heads := []string{}
	for _, week := range weekRows {
		heads = append(heads, week["tile"].(string))
	}
	var wkitemRows []orm.Params
	loadCall = []interface{}{dFormData.Formid, dFormData.Newid}
	results, _ = o.Raw("call foodinfo.searchweekform(?, ?)", loadCall).Values(&wkitemRows)
	items := []map[string]interface{}{}
	for _, wkitem := range wkitemRows {
		weekitems := []map[string]interface{}{}
		if weekRows[0]["outValue"] == "radio" || weekRows[0]["outValue"] == "checkbox" || weekRows[0]["outValue"] == "droplist" {
			var optionRows []orm.Params
			loadCall = []interface{}{weekRows[0]["wkId"]}
			results, _ = o.Raw("call foodinfo.searchwkoptionform(?)", loadCall).Values(&optionRows)
			for _, option := range optionRows {
				weekitems = append(weekitems, map[string]interface{}{"optionPadding": false, "value": option["value"]})
			}
		}
		sttimeitems := []map[string]interface{}{}
		if weekRows[1]["outValue"] == "radio" || weekRows[1]["outValue"] == "checkbox" || weekRows[1]["outValue"] == "droplist" {
			var optionRows []orm.Params
			loadCall = []interface{}{weekRows[1]["wkId"]}
			results, _ = o.Raw("call foodinfo.searchwkoptionform(?)", loadCall).Values(&optionRows)
			for _, option := range optionRows {
				sttimeitems = append(sttimeitems, map[string]interface{}{"optionPadding": false, "value": option["value"]})
			}
		}
		entimeitems := []map[string]interface{}{}
		if weekRows[2]["outValue"] == "radio" || weekRows[2]["outValue"] == "checkbox" || weekRows[2]["outValue"] == "droplist" {
			var optionRows []orm.Params
			loadCall = []interface{}{weekRows[2]["wkId"]}
			results, _ = o.Raw("call foodinfo.searchwkoptionform(?)", loadCall).Values(&optionRows)
			for _, option := range optionRows {
				entimeitems = append(entimeitems, map[string]interface{}{"optionPadding": false, "value": option["value"]})
			}
		}
		items = append(items, map[string]interface{}{"wkId": wkitem["wkId"], "weekId": weekRows[0]["wkId"], "showWeek": true, "weekOutValue": weekRows[0]["outValue"], "weekChecked": weekRows[0]["checked"] == "1", "showWeekDrop": false, "showWeekFile": wkitem["week"] != "", "weekValue": wkitem["week"], "showWeekMenu": false, "weekitems": weekitems, "sttimeId": weekRows[1]["wkId"], "showSttime": true, "sttimeOutValue": weekRows[1]["outValue"], "sttimeChecked": weekRows[1]["checked"] == "1", "showSttimeDrop": false, "showSttimeFile": wkitem["sttime"] != "", "sttimeValue": wkitem["sttime"], "showSttimeMenu": false, "sttimeitems": sttimeitems, "entimeId": weekRows[2]["wkId"], "showEntime": true, "entimeOutValue": weekRows[2]["outValue"], "entimeChecked": weekRows[2]["checked"] == "1", "showEntimeDrop": false, "showEntimeFile": wkitem["entime"] != "", "entimeValue": wkitem["entime"], "showEntimeMenu": false, "entimeitems": entimeitems, "showMore": false, "itemDelete": false, "itemModify": false, "itemCreate": false})
	}
	return &models.SInfoModels{Formid: mainRows[0]["formId"].(string), Tile: mainRows[0]["tile"].(string), Desc: mainRows[0]["desc"].(string), Checked: mainRows[0]["status"] == "1", Heads: heads, Items: items, Status: "istrue"}
}

func GetAddWeekModels(iItemsData models.IItemsData) *models.SItemsModels {
	o := orm.NewOrm()
	var weekRows []orm.Params
	loadCall := []interface{}{}
	results, _ := o.Raw("call foodinfo.searchwkmoduleinfo", loadCall).Values(&weekRows)
	if results == 0 {
		return &models.SItemsModels{Status: "nodata"}
	}
	weekitems := []map[string]interface{}{}
	if weekRows[0]["outValue"] == "droplist" {
		var optionRows []orm.Params
		loadCall = []interface{}{weekRows[0]["wkId"]}
		results, _ = o.Raw("call foodinfo.searchwkoptionform(?)", loadCall).Values(&optionRows)
		for _, option := range optionRows {
			weekitems = append(weekitems, map[string]interface{}{"optionPadding": false, "value": option["value"]})
		}
	}
	weekanswitems := []map[string]interface{}{}
	if weekRows[0]["outValue"] == "radio" || weekRows[0]["outValue"] == "checkbox" {
		var optionRows []orm.Params
		loadCall = []interface{}{weekRows[0]["wkId"]}
		results, _ = o.Raw("call foodinfo.searchwkoptionform(?)", loadCall).Values(&optionRows)
		for _, option := range optionRows {
			weekanswitems = append(weekanswitems, map[string]interface{}{"id": option["id"], "value": option["value"], "showAnswer": false})
		}
	}
	sttimeitems := []map[string]interface{}{}
	if weekRows[1]["outValue"] == "droplist" {
		var optionRows []orm.Params
		loadCall = []interface{}{weekRows[1]["wkId"]}
		results, _ = o.Raw("call foodinfo.searchwkoptionform(?)", loadCall).Values(&optionRows)
		for _, option := range optionRows {
			sttimeitems = append(sttimeitems, map[string]interface{}{"optionPadding": false, "value": option["value"]})
		}
	}
	sttimeanswitems := []map[string]interface{}{}
	if weekRows[1]["outValue"] == "radio" || weekRows[1]["outValue"] == "checkbox" {
		var optionRows []orm.Params
		loadCall = []interface{}{weekRows[1]["wkId"]}
		results, _ = o.Raw("call foodinfo.searchwkoptionform(?)", loadCall).Values(&optionRows)
		for _, option := range optionRows {
			sttimeanswitems = append(sttimeanswitems, map[string]interface{}{"id": option["id"], "value": option["value"], "showAnswer": false})
		}
	}
	entimeitems := []map[string]interface{}{}
	if weekRows[2]["outValue"] == "droplist" {
		var optionRows []orm.Params
		loadCall = []interface{}{weekRows[2]["wkId"]}
		results, _ = o.Raw("call foodinfo.searchwkoptionform(?)", loadCall).Values(&optionRows)
		for _, option := range optionRows {
			entimeitems = append(entimeitems, map[string]interface{}{"optionPadding": false, "value": option["value"]})
		}
	}
	entimeanswitems := []map[string]interface{}{}
	if weekRows[2]["outValue"] == "radio" || weekRows[2]["outValue"] == "checkbox" {
		var optionRows []orm.Params
		loadCall = []interface{}{weekRows[2]["wkId"]}
		results, _ = o.Raw("call foodinfo.searchwkoptionform(?)", loadCall).Values(&optionRows)
		for _, option := range optionRows {
			entimeanswitems = append(entimeanswitems, map[string]interface{}{"id": option["id"], "value": option["value"], "showAnswer": false})
		}
	}
	itemlength := len(iItemsData.Items)
	if itemlength > 0 {
		itemlength, _ = strconv.Atoi(iItemsData.Items[itemlength-1]["wkId"].(string))
	}
	wkid := strconv.Itoa(itemlength + 1)
	items := []map[string]interface{}{}
	items = append(items, map[string]interface{}{"wkId": wkid, "weekId": weekRows[0]["wkId"], "showWeek": true, "weekOutValue": weekRows[0]["outValue"], "weekChecked": weekRows[0]["checked"] == "1", "showWeekDrop": false, "showWeekFile": false, "weekValue": "", "showWeekMenu": false, "weekitems": weekitems, "weekanswitems": weekanswitems, "sttimeId": weekRows[1]["wkId"], "showSttime": true, "sttimeOutValue": weekRows[1]["outValue"], "sttimeChecked": weekRows[1]["checked"] == "1", "showSttimeDrop": false, "showSttimeFile": false, "sttimeValue": "", "showSttimeMenu": false, "sttimeitems": sttimeitems, "sttimeanswitems": sttimeanswitems, "entimeId": weekRows[2]["wkId"], "showEntime": true, "entimeOutValue": weekRows[2]["outValue"], "entimeChecked": weekRows[2]["checked"] == "1", "showEntimeDrop": false, "showEntimeFile": false, "entimeValue": "", "showEntimeMenu": false, "entimeitems": entimeitems, "entimeanswitems": entimeanswitems, "showMore": false, "itemDelete": false, "itemModify": false, "itemCreate": true})
	return &models.SItemsModels{Items: items, Status: "istrue"}
}

func GetInsertModels(iFormData models.IFormData) *models.StatusModels {
	for _, items := range iFormData.Items {
		if items["itemDelete"] == false {
			wrong := appcode.Chkarraystring(items["weekOutValue"].(string), items["weekChecked"].(bool), items["wkId"].(string), items["weekValue"].(string))
			if wrong != "" {
				return &models.StatusModels{Status: wrong}
			}
			wrong = appcode.Chkarraystring(items["sttimeOutValue"].(string), items["sttimeChecked"].(bool), items["wkId"].(string), items["sttimeValue"].(string))
			if wrong != "" {
				return &models.StatusModels{Status: wrong}
			}
			wrong = appcode.Chkarraystring(items["entimeOutValue"].(string), items["entimeChecked"].(bool), items["wkId"].(string), items["entimeValue"].(string))
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
		if items["itemDelete"] == true {
			saveExec := []interface{}{iFormData.Formid, items["wkId"], iFormData.Newid}
			_, err := o.Raw("delete from foodinfo.stweekform where formId = ? and wkId = ? and inoper = ?", saveExec).Exec()
			if err != nil {
				return &models.StatusModels{Status: "error"}
			}
		} else if items["itemCreate"] == true {
			saveExec := []interface{}{iFormData.Formid, items["wkId"], iFormData.Newid, items["weekValue"], items["sttimeValue"], items["entimeValue"]}
			_, err := o.Raw("insert into foodinfo.stweekform (formId,wkId,inoper,week,sttime,entime) values (?, ?, ?, ?, ?, ?)", saveExec).Exec()
			if err != nil {
				return &models.StatusModels{Status: "error"}
			}
		} else {
			saveExec := []interface{}{items["weekValue"], items["sttimeValue"], items["entimeValue"], iFormData.Newid, iFormData.Formid, items["wkId"], iFormData.Newid}
			_, err := o.Raw("update foodinfo.stweekform set week = ?,sttime = ?,entime = ?,mooper = ? where formId = ? and wkId = ? and inoper = ?", saveExec).Exec()
			if err != nil {
				return &models.StatusModels{Status: "error"}
			}
		}
	}
	return &models.StatusModels{Status: "istrue"}
}
