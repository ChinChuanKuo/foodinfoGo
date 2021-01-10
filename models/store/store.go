package store

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

func GetSearchModels(dFormData models.DFormData) *models.SFormsModels {
	if len(strings.TrimSpace(dFormData.Formid)) == 0 {
		return &models.SFormsModels{Status: "errorSearch"}
	}
	/*if !record.SearchRecord(dFormData.Formid, "store", dFormData.Newid) {
		return &models.SFormsModels{Status: "error"}
	}*/
	o := orm.NewOrm()
	var moduleRows []orm.Params
	loadCall := []interface{}{}
	results, _ := o.Raw("call foodinfo.searchstmoduleinfo", loadCall).Values(&moduleRows)
	if results == 0 {
		return &models.SFormsModels{Status: "nodata"}
	}
	var mainRows []orm.Params
	loadCall = []interface{}{dFormData.Formid, dFormData.Newid}
	results, _ = o.Raw("call foodinfo.searchstoreform(?, ?)", loadCall).Values(&mainRows)
	if results == 0 {
		return &models.SFormsModels{Status: "nodata"}
	}
	typeitems := []map[string]interface{}{}
	if moduleRows[0]["outValue"] == "droplist" {
		var optionRows []orm.Params
		loadCall = []interface{}{moduleRows[0]["stId"]}
		results, _ = o.Raw("call foodinfo.searchstoptionform(?)", loadCall).Values(&optionRows)
		for _, option := range optionRows {
			typeitems = append(typeitems, map[string]interface{}{"optionPadding": false, "value": option["value"]})
		}
	}
	typeanswitems := []map[string]interface{}{}
	if moduleRows[0]["outValue"] == "radio" || moduleRows[0]["outValue"] == "checkbox" {
		var optionRows []orm.Params
		loadCall = []interface{}{moduleRows[0]["stId"]}
		results, _ = o.Raw("call foodinfo.searchstoptionform(?)", loadCall).Values(&optionRows)
		for _, option := range optionRows {
			typeanswitems = append(typeanswitems, map[string]interface{}{"id": option["id"], "value": option["value"], "showAnswer": false})
		}
	}
	phoneitems := []map[string]interface{}{}
	if moduleRows[1]["outValue"] == "droplist" {
		var optionRows []orm.Params
		loadCall = []interface{}{moduleRows[1]["stId"]}
		results, _ = o.Raw("call foodinfo.searchstoptionform(?)", loadCall).Values(&optionRows)
		for _, option := range optionRows {
			phoneitems = append(phoneitems, map[string]interface{}{"optionPadding": false, "value": option["value"]})
		}
	}
	phoneanswitems := []map[string]interface{}{}
	if moduleRows[1]["outValue"] == "radio" || moduleRows[1]["outValue"] == "checkbox" {
		var optionRows []orm.Params
		loadCall = []interface{}{moduleRows[1]["stId"]}
		results, _ = o.Raw("call foodinfo.searchstoptionform(?)", loadCall).Values(&optionRows)
		for _, option := range optionRows {
			phoneanswitems = append(phoneanswitems, map[string]interface{}{"id": option["id"], "value": option["value"], "showAnswer": false})
		}
	}
	addritems := []map[string]interface{}{}
	if moduleRows[2]["outValue"] == "droplist" {
		var optionRows []orm.Params
		loadCall = []interface{}{moduleRows[2]["stId"]}
		results, _ = o.Raw("call foodinfo.searchstoptionform(?)", loadCall).Values(&optionRows)
		for _, option := range optionRows {
			addritems = append(addritems, map[string]interface{}{"optionPadding": false, "value": option["value"]})
		}
	}
	addranswitems := []map[string]interface{}{}
	if moduleRows[2]["outValue"] == "radio" || moduleRows[2]["outValue"] == "checkbox" {
		var optionRows []orm.Params
		loadCall = []interface{}{moduleRows[2]["stId"]}
		results, _ = o.Raw("call foodinfo.searchstoptionform(?)", loadCall).Values(&optionRows)
		for _, option := range optionRows {
			addranswitems = append(addranswitems, map[string]interface{}{"id": option["id"], "value": option["value"], "showAnswer": false})
		}
	}
	items := []map[string]interface{}{}
	items = append(items, map[string]interface{}{"typeId": moduleRows[0]["stId"], "showType": true, "typeOutValue": moduleRows[0]["outValue"], "typeChecked": moduleRows[0]["checked"] == "1", "showTypeDrop": false, "showTypeFile": mainRows[0]["type"] != "", "typeTitle": moduleRows[0]["tile"], "typeValue": mainRows[0]["type"], "showTypeMenu": false, "typeitems": typeitems, "typeanswitems": typeanswitems, "phoneId": moduleRows[1]["stId"], "showPhone": true, "phoneOutValue": moduleRows[1]["outValue"], "phoneChecked": moduleRows[1]["checked"] == "1", "showPhoneDrop": false, "showPhoneFile": mainRows[0]["phone"] != "", "phoneTitle": moduleRows[1]["tile"], "phoneValue": mainRows[0]["phone"], "showPhoneMenu": false, "phoneitems": phoneitems, "phoneanswitems": phoneanswitems, "addrId": moduleRows[2]["stId"], "showAddr": true, "addrOutValue": moduleRows[2]["outValue"], "addrChecked": moduleRows[2]["checked"] == "1", "showAddrDrop": false, "showAddrFile": mainRows[0]["address"] != "", "addrTitle": moduleRows[2]["tile"], "addrValue": mainRows[0]["address"], "showAddrMenu": false, "addritems": addritems, "addranswitems": addranswitems})
	return &models.SFormsModels{Formid: mainRows[0]["formId"].(string), Tile: mainRows[0]["tile"].(string), Desc: mainRows[0]["desc"].(string), Checked: mainRows[0]["status"] == "1", Items: items, Status: "istrue"}
}

func GetInsertModels(iFormData models.IFormData) *models.StatusModels {
	for _, items := range iFormData.Items {
		wrong := appcode.Chkarraystring(items["typeOutValue"].(string), items["typeChecked"].(bool), items["typeTitle"].(string), items["typeValue"].(string))
		if wrong != "" {
			return &models.StatusModels{Status: wrong}
		}
		wrong = appcode.Chkarraystring(items["phoneOutValue"].(string), items["phoneChecked"].(bool), items["phoneTitle"].(string), items["phoneValue"].(string))
		if wrong != "" {
			return &models.StatusModels{Status: wrong}
		}
		wrong = appcode.Chkarraystring(items["addrOutValue"].(string), items["addrChecked"].(bool), items["addrTitle"].(string), items["addrValue"].(string))
		if wrong != "" {
			return &models.StatusModels{Status: wrong}
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
	location := appcode.GetLocation(iFormData.Items[0]["addrValue"].(string))
	if mainRows[0]["type"] != iFormData.Items[0]["typeValue"] || mainRows[0]["phone"] != iFormData.Items[0]["phoneValue"] || mainRows[0]["address"] != iFormData.Items[0]["addrValue"] || mainRows[0]["longitude"] != location[0] || mainRows[0]["latitude"] != location[1] {
		saveExec := []interface{}{iFormData.Items[0]["typeValue"], iFormData.Items[0]["phoneValue"], iFormData.Items[0]["addrValue"], location[0], location[1], iFormData.Newid, iFormData.Formid, iFormData.Newid}
		_, err := o.Raw("update foodinfo.stsubform set type = ?,phone = ?,address = ?,longitude = ?,latitude = ?,mooper = ? where formId = ? and inoper = ?", saveExec).Exec()
		if err != nil {
			return &models.StatusModels{Status: "error"}
		}
	}
	return &models.StatusModels{Status: "istrue"}
}
