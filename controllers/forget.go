package controllers

import (
	"encoding/json"
	"foodinfoGo/models"
	"foodinfoGo/models/forget"

	"github.com/astaxie/beego"
)

type ForgetController struct {
	beego.Controller
}

func (this *ForgetController) ForgetUserData() {
	others := models.OtherData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &others); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = forget.GetForgetUserModels(others)
	this.ServeJSON()
}
