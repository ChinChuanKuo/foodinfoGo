package home

import (
	"fmt"
	"foodinfoGo/appcode"
	"foodinfoGo/models"
	"strconv"
	"strings"
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

func GetPollingModels(sLocalData models.SLocalData) *models.SOptionModels {
	o := orm.NewOrm()
	var mainRows []orm.Params
	loadCall := []interface{}{sLocalData.Length, sLocalData.Longitude, sLocalData.Latitude}
	_, err := o.Raw("call foodinfo.searchstoreing(?, ?, ?)", loadCall).Values(&mainRows)
	if err != nil {
		return &models.SOptionModels{Items: []map[string]interface{}{}}
	}
	items := []map[string]interface{}{}
	longitude, _ := strconv.ParseFloat(sLocalData.Longitude, 64)
	latitude, _ := strconv.ParseFloat(sLocalData.Latitude, 64)
	for _, main := range mainRows {
		distance := "未填寫地址"
		arrival := "無法測量"
		if main["longitude"] != "" && main["latitude"] != "" {
			storelongitude, _ := strconv.ParseFloat(main["longitude"].(string), 64)
			storelatitude, _ := strconv.ParseFloat(main["latitude"].(string), 64)
			distanceMatrix := appcode.GetDistanceMatrix("walking", "zh-TW", longitude, storelongitude, latitude, storelatitude)
			//distance = appcode.GetDistanceUnit(appcode.GetDistance(longitude, storelongitude, latitude, storelatitude))
			distance = distanceMatrix[1]
			arrival = distanceMatrix[0]
			//direction = appcode.GetDirections("walking", "zh-TW", longitude, storelongitude, latitude, storelatitude)
		}
		items = append(items, map[string]interface{}{"id": main["formId"], "tile": main["tile"], "desc": main["desc"], "distance": distance, "arrival": arrival, "enter": false})
	}
	return &models.SOptionModels{Items: items}
}

func GetSearchModels(sLocalData models.SLocalData) *models.SItemsModels {
	if len(strings.TrimSpace(sLocalData.Newid)) == 0 {
		return &models.SItemsModels{Status: "errorSearch"}
	}
	o := orm.NewOrm()
	var countRows []orm.Params
	loadCall := []interface{}{sLocalData.Longitude, sLocalData.Latitude}
	results, _ := o.Raw("call foodinfo.countstoreitem(?, ?)", loadCall).Values(&countRows)
	if results == 0 {
		return &models.SItemsModels{Status: "nodata"}
	}
	var mainRows []orm.Params
	loadCall = []interface{}{sLocalData.Length, sLocalData.Longitude, sLocalData.Latitude}
	results, _ = o.Raw("call foodinfo.searchstoreitem(?, ?, ?)", loadCall).Values(&mainRows)
	if results == 0 {
		return &models.SItemsModels{Status: "nodata"}
	}
	longitude, _ := strconv.ParseFloat(sLocalData.Longitude, 64)
	latitude, _ := strconv.ParseFloat(sLocalData.Latitude, 64)
	items := []map[string]interface{}{}
	for _, main := range mainRows {
		distance := "未填寫地址"
		arrival := "無法測量"
		if main["longitude"] != "" && main["latitude"] != "" {
			storelongitude, _ := strconv.ParseFloat(main["longitude"].(string), 64)
			storelatitude, _ := strconv.ParseFloat(main["latitude"].(string), 64)
			distanceMatrix := appcode.GetDistanceMatrix("walking", "zh-TW", longitude, storelongitude, latitude, storelatitude)
			//distance = appcode.GetDistanceUnit(appcode.GetDistance(longitude, storelongitude, latitude, storelatitude))
			distance = distanceMatrix[1]
			arrival = distanceMatrix[0]
			//direction = appcode.GetDirections("walking", "zh-TW", longitude, storelongitude, latitude, storelatitude)
		}
		items = append(items, map[string]interface{}{"id": main["formId"], "tile": main["tile"], "desc": main["desc"], "distance": distance, "arrival": arrival, "enter": false})
	}
	counts, _ := strconv.Atoi(countRows[0]["counts"].(string))
	return &models.SItemsModels{Showitem: counts != sLocalData.Length+len(mainRows), Items: items, Status: "istrue"}
}

func GetScrollModels(sLocalData models.SLocalData) *models.ItemsModels {
	o := orm.NewOrm()
	var countRows []orm.Params
	loadCall := []interface{}{sLocalData.Longitude, sLocalData.Latitude}
	results, _ := o.Raw("call foodinfo.countstoreitem(?, ?)", loadCall).Values(&countRows)
	if results == 0 {
		return &models.ItemsModels{Showitem: false}
	}
	var mainRows []orm.Params
	loadCall = []interface{}{sLocalData.Length, sLocalData.Longitude, sLocalData.Latitude}
	results, _ = o.Raw("call foodinfo.searchstoreitem(?, ?, ?)", loadCall).Values(&mainRows)
	if results == 0 {
		return &models.ItemsModels{Showitem: false}
	}
	longitude, _ := strconv.ParseFloat(sLocalData.Longitude, 64)
	latitude, _ := strconv.ParseFloat(sLocalData.Latitude, 64)
	items := []map[string]interface{}{}
	for _, main := range mainRows {
		distance := "未填寫地址"
		arrival := "無法測量"
		if main["longitude"] != "" && main["latitude"] != "" {
			storelongitude, _ := strconv.ParseFloat(main["longitude"].(string), 64)
			storelatitude, _ := strconv.ParseFloat(main["latitude"].(string), 64)
			distanceMatrix := appcode.GetDistanceMatrix("walking", "zh-TW", longitude, storelongitude, latitude, storelatitude)
			//distance = appcode.GetDistanceUnit(appcode.GetDistance(longitude, storelongitude, latitude, storelatitude))
			distance = distanceMatrix[1]
			arrival = distanceMatrix[0]
			//direction = appcode.GetDirections("walking", "zh-TW", longitude, storelongitude, latitude, storelatitude)
		}
		items = append(items, map[string]interface{}{"id": main["formId"], "tile": main["tile"], "desc": main["desc"], "distance": distance, "arrival": arrival, "enter": false})
	}
	counts, _ := strconv.Atoi(countRows[0]["counts"].(string))
	return &models.ItemsModels{Showitem: counts != sLocalData.Length+len(mainRows), Items: items}
}

func GetPingItemModels(sPChatData models.SPChatData) *models.SOptionModels {
	o := orm.NewOrm()
	isbreak := true
	items := []map[string]interface{}{}
	for isbreak {
		time.Sleep(time.Duration(5) * time.Second)
		var countRows []orm.Params
		loadCall := []interface{}{sPChatData.Formid}
		_, err := o.Raw("call foodinfo.countmenuitem(?)", loadCall).Values(&countRows)
		if err != nil {
			isbreak = false
		}
		counts, _ := strconv.Atoi(countRows[0]["counts"].(string))
		if counts > sPChatData.Length {
			var mainRows []orm.Params
			loadCall = []interface{}{sPChatData.Formid, counts - sPChatData.Length}
			_, err = o.Raw("call foodinfo.searchmenuing(?, ?)", loadCall).Values(&mainRows)
			datetime := appcode.GetDateTime()
			for _, main := range mainRows {
				items = append(items, map[string]interface{}{"id": main["formId"].(string) + "#" + main["ctId"].(string), "fstName": appcode.Substring(main["username"].(string), 0, 1), "content": main["content"], "datetime": appcode.GetDaysOrHours(main["indate"].(string)+" "+main["intime"].(string), datetime), "name": main["username"], "itemDelete": main["inoper"] == sPChatData.Newid, "showEnter": false})
			}
			isbreak = false
		}
	}
	return &models.SOptionModels{Items: items}
}

func GetSItemModels(dFormData models.DFormData) *models.SFormsModels {
	o := orm.NewOrm()
	var mainRows []orm.Params
	loadCall := []interface{}{dFormData.Formid}
	results, _ := o.Raw("call foodinfo.searchstoredeta(?)", loadCall).Values(&mainRows)
	if results == 0 {
		return &models.SFormsModels{Status: "nodata"}
	}
	var menuRows []orm.Params
	results, _ = o.Raw("call foodinfo.searchmenudeta(?)", loadCall).Values(&menuRows)
	menuitems := []map[string]interface{}{}
	for _, menu := range menuRows {
		menuitems = append(menuitems, map[string]interface{}{"id": menu["formId"].(string) + "#" + menu["muId"].(string), "name": menu["name"], "price": menu["price"], "allergy": menu["allergy"], "album": menu["album"], "remark": menu["remark"]})
	}
	items := []map[string]interface{}{}
	items = append(items, map[string]interface{}{"type_": mainRows[0]["type"], "phone": mainRows[0]["phone"], "address": mainRows[0]["address"], "menuitems": menuitems})
	return &models.SFormsModels{Formid: mainRows[0]["formId"].(string), Tile: mainRows[0]["tile"].(string), Desc: mainRows[0]["desc"].(string), Checked: mainRows[0]["status"] == "1", Items: items, Status: "istrue"}
}

func GetPingChatModels(sPChatData models.SPChatData) *models.SOptionModels {
	o := orm.NewOrm()
	isbreak := true
	items := []map[string]interface{}{}
	for isbreak {
		time.Sleep(time.Duration(5) * time.Second)
		var countRows []orm.Params
		loadCall := []interface{}{sPChatData.Formid}
		_, err := o.Raw("call foodinfo.countchatitem(?)", loadCall).Values(&countRows)
		if err != nil {
			isbreak = false
		}
		counts, _ := strconv.Atoi(countRows[0]["counts"].(string))
		if counts > sPChatData.Length {
			var mainRows []orm.Params
			loadCall = []interface{}{sPChatData.Formid, counts - sPChatData.Length}
			_, err = o.Raw("call foodinfo.searchchating(?, ?)", loadCall).Values(&mainRows)
			datetime := appcode.GetDateTime()
			for _, main := range mainRows {
				items = append(items, map[string]interface{}{"id": main["formId"].(string) + "#" + main["ctId"].(string), "fstName": appcode.Substring(main["username"].(string), 0, 1), "content": main["content"], "datetime": appcode.GetDaysOrHours(main["indate"].(string)+" "+main["intime"].(string), datetime), "name": main["username"], "itemDelete": main["inoper"] == sPChatData.Newid, "showEnter": false})
			}
			isbreak = false
		}
	}
	return &models.SOptionModels{Items: items}
}

func GetSChatModels(sPChatData models.SPChatData) *models.SItemModels {
	o := orm.NewOrm()
	var countRows []orm.Params
	loadCall := []interface{}{sPChatData.Formid}
	_, err := o.Raw("call foodinfo.countchatitem(?)", loadCall).Values(&countRows)
	if err != nil {
		return &models.SItemModels{Status: "nodata"}
	}
	counts, _ := strconv.Atoi(countRows[0]["counts"].(string))
	if counts <= sPChatData.Length {
		return &models.SItemModels{Status: "nodata"}
	}
	var mainRows []orm.Params
	loadCall = []interface{}{sPChatData.Formid}
	sqlCode := "call foodinfo.searchchatdeta(?)"
	if sPChatData.Length > 0 {
		loadCall = []interface{}{sPChatData.Formid, counts - sPChatData.Length}
		sqlCode = "call foodinfo.searchchating(?, ?)"
	}
	results, _ := o.Raw(sqlCode, loadCall).Values(&mainRows)
	if results == 0 {
		return &models.SItemModels{Status: "nodata"}
	}
	datetime := appcode.GetDateTime()
	items := []map[string]interface{}{}
	for _, main := range mainRows {
		items = append(items, map[string]interface{}{"id": main["formId"].(string) + "#" + main["ctId"].(string), "fstName": appcode.Substring(main["username"].(string), 0, 1), "content": main["content"], "datetime": appcode.GetDaysOrHours(main["indate"].(string)+" "+main["intime"].(string), datetime), "name": main["username"], "itemDelete": main["inoper"] == sPChatData.Newid, "showEnter": false})
	}
	return &models.SItemModels{Items: items, Status: "istrue"}
}

func GetStoreModels(userData models.UserData) *models.SFormModels {
	o := orm.NewOrm()
	var mainRows []orm.Params
	loadCall := []interface{}{userData.Userid}
	results, _ := o.Raw("call foodinfo.searchstoreinfo(?)", loadCall).Values(&mainRows)
	if results == 0 {
		return &models.SFormModels{Status: "nodata"}
	}
	return &models.SFormModels{Formid: mainRows[0]["formId"].(string), Status: "istrue"}
}

func GetCreateModels(userData models.UserData) *models.SFormModels {
	o := orm.NewOrm()
	var mainRows []orm.Params
	loadCall := []interface{}{userData.Userid}
	results, _ := o.Raw("call foodinfo.createstoreform(?)", loadCall).Values(&mainRows)
	if results == 0 {
		return &models.SFormModels{Status: "nodata"}
	}
	return &models.SFormModels{Formid: mainRows[0]["formId"].(string), Status: "istrue"}
}
