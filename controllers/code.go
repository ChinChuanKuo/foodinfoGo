package controllers

import (
	"encoding/json"
	"foodinfoGo/models"
	"foodinfoGo/models/code"

	beego "github.com/beego/beego/v2/server/web"
)

type CodeController struct {
	beego.Controller
}

func (this *CodeController) CodeUserData() {
	others := models.OtherData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &others); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = code.GetCodeUserModels(others)
	this.ServeJSON()
}
