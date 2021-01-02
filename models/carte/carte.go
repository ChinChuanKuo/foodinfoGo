package carte

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

func GetSearchModels(dFormData models.DFormData) *models.SFormsModels {
	if len(strings.TrimSpace(dFormData.Formid)) == 0 {
		return &models.SFormsModels{Status: "errorSearch"}
	}
	o := orm.NewOrm()
	var mainRows []orm.Params
	loadCall := []interface{}{dFormData.Formid, dFormData.Newid}
	results, _ := o.Raw("call foodinfo.searchstoreform(?, ?)", loadCall).Values(&mainRows)
	if results == 0 {
		return &models.SFormsModels{Status: "nodata"}
	}
	var moduleRows []orm.Params
	loadCall = []interface{}{}
	results, _ = o.Raw("call foodinfo.searchmumoduleinfo", loadCall).Values(&moduleRows)
	if results == 0 {
		return &models.SFormsModels{Status: "nodata"}
	}
	var menuRows []orm.Params
	loadCall = []interface{}{dFormData.Formid, dFormData.Newid}
	results, _ = o.Raw("call foodinfo.searchmenuform(?, ?)", loadCall).Values(&menuRows)
	items := []map[string]interface{}{}
	for _, menu := range menuRows {
		nameitems := []map[string]interface{}{}
		if moduleRows[0]["outValue"] == "radio" || moduleRows[0]["outValue"] == "checkbox" || moduleRows[0]["outValue"] == "droplist" {
			var optionRows []orm.Params
			loadCall = []interface{}{moduleRows[0]["muId"]}
			results, _ = o.Raw("call foodinfo.searchmuoptionform(?)", loadCall).Values(&optionRows)
			for _, option := range optionRows {
				nameitems = append(nameitems, map[string]interface{}{"optionPadding": false, "value": option["value"]})
			}
		}
		priceitems := []map[string]interface{}{}
		if moduleRows[1]["outValue"] == "radio" || moduleRows[1]["outValue"] == "checkbox" || moduleRows[1]["outValue"] == "droplist" {
			var optionRows []orm.Params
			loadCall = []interface{}{moduleRows[1]["muId"]}
			results, _ = o.Raw("call foodinfo.searchmuoptionform(?)", loadCall).Values(&optionRows)
			for _, option := range optionRows {
				priceitems = append(priceitems, map[string]interface{}{"optionPadding": false, "value": option["value"]})
			}
		}
		allergyitems := []map[string]interface{}{}
		if moduleRows[2]["outValue"] == "radio" || moduleRows[2]["outValue"] == "checkbox" || moduleRows[2]["outValue"] == "droplist" {
			var optionRows []orm.Params
			loadCall = []interface{}{moduleRows[2]["muId"]}
			results, _ = o.Raw("call foodinfo.searchmuoptionform(?)", loadCall).Values(&optionRows)
			for _, option := range optionRows {
				allergyitems = append(allergyitems, map[string]interface{}{"optionPadding": false, "value": option["value"]})
			}
		}
		albumitems := []map[string]interface{}{}
		if moduleRows[3]["outValue"] == "radio" || moduleRows[3]["outValue"] == "checkbox" || moduleRows[3]["outValue"] == "droplist" {
			var optionRows []orm.Params
			loadCall = []interface{}{moduleRows[3]["muId"]}
			results, _ = o.Raw("call foodinfo.searchmuoptionform(?)", loadCall).Values(&optionRows)
			for _, option := range optionRows {
				albumitems = append(albumitems, map[string]interface{}{"optionPadding": false, "value": option["value"]})
			}
		}
		remarkitems := []map[string]interface{}{}
		if moduleRows[4]["outValue"] == "radio" || moduleRows[4]["outValue"] == "checkbox" || moduleRows[4]["outValue"] == "droplist" {
			var optionRows []orm.Params
			loadCall = []interface{}{moduleRows[4]["muId"]}
			results, _ = o.Raw("call foodinfo.searchmuoptionform(?)", loadCall).Values(&optionRows)
			for _, option := range optionRows {
				remarkitems = append(remarkitems, map[string]interface{}{"optionPadding": false, "value": option["value"]})
			}
		}
		items = append(items, map[string]interface{}{"muId": menu["muId"], "nameId": moduleRows[0]["muId"], "showName": true, "nameOutValue": moduleRows[0]["outValue"], "nameChecked": moduleRows[0]["checked"] == "1", "showNameDrop": false, "showNameFile": menu["name"] != "", "nameTitle": moduleRows[0]["tile"], "nameValue": menu["name"], "showNameMenu": false, "nameitems": nameitems, "priceId": moduleRows[1]["muId"], "showPrice": true, "priceOutValue": moduleRows[1]["outValue"], "priceChecked": moduleRows[1]["checked"] == "1", "showPriceDrop": false, "showPriceFile": menu["price"] != "", "priceTitle": moduleRows[1]["tile"], "priceValue": menu["price"], "showPriceMenu": false, "priceitems": priceitems, "allergyId": moduleRows[2]["muId"], "showAllergy": true, "allergyOutValue": moduleRows[2]["outValue"], "allergyChecked": moduleRows[2]["checked"] == "1", "showAllergyDrop": false, "showAllergyFile": menu["allergy"] != "", "allergyTitle": moduleRows[2]["tile"], "allergyValue": menu["allergy"], "showAllergyMenu": false, "allergyitems": allergyitems, "albumId": moduleRows[3]["muId"], "showAlbum": true, "albumOutValue": moduleRows[3]["outValue"], "albumChecked": moduleRows[3]["checked"] == "1", "showAlbumDrop": false, "showAlbumFile": menu["album"] != "", "albumTitle": moduleRows[3]["tile"], "albumValue": menu["album"], "showAlbumMenu": false, "albumitems": albumitems, "remarkId": moduleRows[4]["muId"], "showRemark": true, "remarkOutValue": moduleRows[4]["outValue"], "remarkChecked": moduleRows[4]["checked"] == "1", "showRemarkDrop": false, "showRemarkFile": menu["remark"] != "", "remarkTitle": moduleRows[4]["tile"], "remarkValue": menu["remark"], "showRemarkMenu": false, "remarkitems": remarkitems, "showMore": false, "showDelete": false, "showModify": false, "showCreate": false})
	}
	return &models.SFormsModels{Formid: mainRows[0]["formId"].(string), Tile: mainRows[0]["tile"].(string), Desc: mainRows[0]["desc"].(string), Checked: mainRows[0]["status"] == "1", Items: items, Status: "istrue"}
}

func GetAddMenuModels(iItemsData models.IItemsData) *models.SItemsModels {
	o := orm.NewOrm()
	var menuRows []orm.Params
	loadCall := []interface{}{}
	results, _ := o.Raw("call foodinfo.searchmumoduleinfo", loadCall).Values(&menuRows)
	if results == 0 {
		return &models.SItemsModels{Status: "nodata"}
	}
	nameitems := []map[string]interface{}{}
	if menuRows[0]["outValue"] == "radio" || menuRows[0]["outValue"] == "checkbox" || menuRows[0]["outValue"] == "droplist" {
		var optionRows []orm.Params
		loadCall = []interface{}{menuRows[0]["muId"]}
		results, _ = o.Raw("call foodinfo.searchmuoptionform(?)", loadCall).Values(&optionRows)
		for _, option := range optionRows {
			nameitems = append(nameitems, map[string]interface{}{"optionPadding": false, "value": option["value"]})
		}
	}
	priceitems := []map[string]interface{}{}
	if menuRows[1]["outValue"] == "radio" || menuRows[1]["outValue"] == "checkbox" || menuRows[1]["outValue"] == "droplist" {
		var optionRows []orm.Params
		loadCall = []interface{}{menuRows[1]["muId"]}
		results, _ = o.Raw("call foodinfo.searchmuoptionform(?)", loadCall).Values(&optionRows)
		for _, option := range optionRows {
			priceitems = append(priceitems, map[string]interface{}{"optionPadding": false, "value": option["value"]})
		}
	}
	allergyitems := []map[string]interface{}{}
	if menuRows[2]["outValue"] == "radio" || menuRows[2]["outValue"] == "checkbox" || menuRows[2]["outValue"] == "droplist" {
		var optionRows []orm.Params
		loadCall = []interface{}{menuRows[2]["muId"]}
		results, _ = o.Raw("call foodinfo.searchmuoptionform(?)", loadCall).Values(&optionRows)
		for _, option := range optionRows {
			allergyitems = append(allergyitems, map[string]interface{}{"optionPadding": false, "value": option["value"]})
		}
	}
	albumitems := []map[string]interface{}{}
	if menuRows[3]["outValue"] == "radio" || menuRows[3]["outValue"] == "checkbox" || menuRows[3]["outValue"] == "droplist" {
		var optionRows []orm.Params
		loadCall = []interface{}{menuRows[3]["muId"]}
		results, _ = o.Raw("call foodinfo.searchmuoptionform(?)", loadCall).Values(&optionRows)
		for _, option := range optionRows {
			albumitems = append(albumitems, map[string]interface{}{"optionPadding": false, "value": option["value"]})
		}
	}
	remarkitems := []map[string]interface{}{}
	if menuRows[4]["outValue"] == "radio" || menuRows[4]["outValue"] == "checkbox" || menuRows[4]["outValue"] == "droplist" {
		var optionRows []orm.Params
		loadCall = []interface{}{menuRows[4]["muId"]}
		results, _ = o.Raw("call foodinfo.searchmuoptionform(?)", loadCall).Values(&optionRows)
		for _, option := range optionRows {
			remarkitems = append(remarkitems, map[string]interface{}{"optionPadding": false, "value": option["value"]})
		}
	}
	itemlength := len(iItemsData.Items)
	if itemlength > 0 {
		itemlength, _ = strconv.Atoi(iItemsData.Items[itemlength-1]["muId"].(string))
	}
	muid := strconv.Itoa(itemlength + 1)
	items := []map[string]interface{}{}
	items = append(items, map[string]interface{}{"muId": muid, "nameId": menuRows[0]["muId"], "showName": true, "nameOutValue": menuRows[0]["outValue"], "nameChecked": menuRows[0]["checked"] == "1", "showNameDrop": false, "showNameFile": false, "nameTitle": menuRows[0]["tile"], "nameValue": "", "showNameMenu": false, "nameitems": nameitems, "priceId": menuRows[1]["muId"], "showPrice": true, "priceOutValue": menuRows[1]["outValue"], "priceChecked": menuRows[1]["checked"] == "1", "showPriceDrop": false, "showPriceFile": false, "priceTitle": menuRows[1]["tile"], "priceValue": "", "showPriceMenu": false, "priceitems": priceitems, "allergyId": menuRows[2]["muId"], "showAllergy": true, "allergyOutValue": menuRows[2]["outValue"], "allergyChecked": menuRows[2]["checked"] == "1", "showAllergyDrop": false, "showAllergyFile": false, "allergyTitle": menuRows[2]["tile"], "allergyValue": "", "showAllergyMenu": false, "allergyitems": allergyitems, "albumId": menuRows[3]["muId"], "showAlbum": true, "albumOutValue": menuRows[3]["outValue"], "albumChecked": menuRows[3]["checked"] == "1", "showAlbumDrop": false, "showAlbumFile": false, "albumTitle": menuRows[3]["tile"], "albumValue": "", "showAlbumMenu": false, "albumitems": albumitems, "remarkId": menuRows[4]["muId"], "showRemark": true, "remarkOutValue": menuRows[4]["outValue"], "remarkChecked": menuRows[4]["checked"] == "1", "showRemarkDrop": false, "showRemarkFile": false, "remarkTitle": menuRows[4]["tile"], "remarkValue": "", "showRemarkMenu": false, "remarkitems": remarkitems, "showMore": false, "showDelete": false, "showModify": false, "showCreate": true})
	return &models.SItemsModels{Items: items, Status: "istrue"}
}

func GetInsertModels(iFormData models.IFormData) *models.StatusModels {
	for _, items := range iFormData.Items {
		if items["showDelete"] == false {
			wrong := appcode.Chkarraystring(items["nameOutValue"].(string), items["nameChecked"].(bool), items["nameTitle"].(string), items["nameValue"].(string))
			if wrong != "" {
				return &models.StatusModels{Status: wrong}
			}
			wrong = appcode.Chkarraystring(items["nameOutValue"].(string), items["priceChecked"].(bool), items["priceTitle"].(string), items["priceValue"].(string))
			if wrong != "" {
				return &models.StatusModels{Status: wrong}
			}
			wrong = appcode.Chkarraystring(items["priceOutValue"].(string), items["nameChecked"].(bool), items["nameTitle"].(string), items["nameValue"].(string))
			if wrong != "" {
				return &models.StatusModels{Status: wrong}
			}
			wrong = appcode.Chkarraystring(items["allergyOutValue"].(string), items["allergyChecked"].(bool), items["allergyTitle"].(string), items["allergyValue"].(string))
			if wrong != "" {
				return &models.StatusModels{Status: wrong}
			}
			wrong = appcode.Chkarraystring(items["albumOutValue"].(string), items["albumChecked"].(bool), items["albumTitle"].(string), items["albumValue"].(string))
			if wrong != "" {
				return &models.StatusModels{Status: wrong}
			}
			wrong = appcode.Chkarraystring(items["remarkOutValue"].(string), items["remarkChecked"].(bool), items["remarkTitle"].(string), items["remarkValue"].(string))
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
		if items["showDelete"] == true {
			saveExec := []interface{}{iFormData.Formid, items["muId"], iFormData.Newid}
			_, err := o.Raw("delete from foodinfo.stmenuform where formId = ? and muId = ? and inoper = ?", saveExec).Exec()
			if err != nil {
				return &models.StatusModels{Status: "error"}
			}
		} else if items["showCreate"] == true {
			saveExec := []interface{}{iFormData.Formid, items["muId"], iFormData.Newid, items["nameValue"], items["priceValue"], items["allergyValue"], items["albumValue"], items["remarkValue"]}
			_, err := o.Raw("insert into foodinfo.stmenuform (formId,muId,inoper,name,price,allergy,album,remark) values (?, ?, ?, ?, ?, ?, ?, ?)", saveExec).Exec()
			if err != nil {
				return &models.StatusModels{Status: "error"}
			}
		} else {
			saveExec := []interface{}{items["nameValue"], items["priceValue"], items["allergyValue"], items["albumValue"], items["remarkValue"], iFormData.Newid, iFormData.Formid, items["muId"], iFormData.Newid}
			_, err := o.Raw("update foodinfo.stmenuform set name = ?,price = ?,allergy = ?,album = ?,remark = ?,mooper = ? where formId = ? and muId = ? and inoper = ?;", saveExec).Exec()
			if err != nil {
				return &models.StatusModels{Status: "error"}
			}
		}
	}
	return &models.StatusModels{Status: "istrue"}
}
