package controllers

import (
	"encoding/json"
	"foodinfoGo/models"
	"foodinfoGo/models/forget"

	beego "github.com/beego/beego/v2/server/web"
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
