package controllers

import (
	"encoding/json"
	"foodinfoGo/models"
	"foodinfoGo/models/resend"

	beego "github.com/beego/beego/v2/server/web"
)

type ResendController struct {
	beego.Controller
}

func (this *ResendController) ResendUserData() {
	others := models.OtherData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &others); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = resend.GetResendUserModels(others)
	this.ServeJSON()
}
