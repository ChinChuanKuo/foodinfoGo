package controllers

import (
	"encoding/json"
	"foodinfoGo/models"
	"foodinfoGo/models/signup"

	"github.com/astaxie/beego"
)

type SignupController struct {
	beego.Controller
}

func (this *SignupController) SignupUserData() {
	signups := models.SignupData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &signups); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = signup.GetSignupUserModels(signups)
	this.ServeJSON()
}
