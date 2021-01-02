package controllers

import (
	"encoding/json"
	"foodinfoGo/models"
	"foodinfoGo/models/login"

	"github.com/astaxie/beego"
)

type LoginController struct {
	beego.Controller
}

func (this *LoginController) CheckUserData() {
	users := models.UserData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &users); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = login.GetUserModels(users)
	this.ServeJSON()
}

func (this *LoginController) LoginUserData() {
	logins := models.LoginData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &logins); err != nil {
		panic(err.Error())
	}
	userAgent := this.Ctx.Input.Header("user-agent")
	this.Data["json"] = login.GetLoginModels(logins, userAgent)
	this.ServeJSON()
}
