package controllers

import (
	"encoding/json"
	"foodinfoGo/models"
	"foodinfoGo/models/form"

	beego "github.com/beego/beego/v2/server/web"
)

type FormController struct {
	beego.Controller
}

func (this *FormController) CheckNewData() {
	users := models.UserData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &users); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = form.GetCheckNewModels(users)
	this.ServeJSON()
}

func (this *FormController) LoginFormData() {
	users := models.UserData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &users); err != nil {
		panic(err.Error())
	}
	userAgent := this.Ctx.Input.Header("user-agent")
	this.Data["json"] = form.GetLoginFormModels(users, userAgent)
	this.ServeJSON()
}

func (this *FormController) BadgeFormData() {
	others := models.OtherData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &others); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = form.GetBadgeFormModels(others)
	this.ServeJSON()
}

func (this *FormController) PermissData() {
	users := models.UserData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &users); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = form.GetPermissModels(users)
	this.ServeJSON()
}

func (this *FormController) RecordData() {
	users := models.UserData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &users); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = form.GetRecordModels(users)
	this.ServeJSON()
}

func (this *FormController) BadgeData() {
	users := models.UserData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &users); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = form.GetBadgeModels(users)
	this.ServeJSON()
}
