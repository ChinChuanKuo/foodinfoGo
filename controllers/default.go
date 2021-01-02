package controllers

import (
	"encoding/json"
	"foodinfoGo/models"
	"foodinfoGo/models/home"

	"github.com/astaxie/beego"
)

type MainController struct {
	beego.Controller
}

func (this *MainController) Get() {
	this.TplName = "index.tpl"
}

func (this *MainController) PollingData() {
	slocal := models.SLocalData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &slocal); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = home.GetPollingModels(slocal)
	this.ServeJSON()
}

func (this *MainController) SearchData() {
	slocal := models.SLocalData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &slocal); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = home.GetSearchModels(slocal)
	this.ServeJSON()
}

func (this *MainController) ScrollData() {
	slocal := models.SLocalData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &slocal); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = home.GetScrollModels(slocal)
	this.ServeJSON()
}

func (this *MainController) PingItemData() {
	spchat := models.SPChatData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &spchat); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = home.GetPingItemModels(spchat)
	this.ServeJSON()
}

func (this *MainController) SItemData() {
	dform := models.DFormData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &dform); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = home.GetSItemModels(dform)
	this.ServeJSON()
}

func (this *MainController) PingChatData() {
	spchat := models.SPChatData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &spchat); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = home.GetPingChatModels(spchat)
	this.ServeJSON()
}

func (this *MainController) SChatData() {
	spchat := models.SPChatData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &spchat); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = home.GetSChatModels(spchat)
	this.ServeJSON()
}

func (this *MainController) StoreData() {
	users := models.UserData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &users); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = home.GetStoreModels(users)
	this.ServeJSON()
}

func (this *MainController) CreateData() {
	users := models.UserData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &users); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = home.GetCreateModels(users)
	this.ServeJSON()
}
