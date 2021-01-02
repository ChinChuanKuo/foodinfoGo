package controllers

import (
	"encoding/json"
	"foodinfoGo/models"
	"foodinfoGo/models/icon"

	"github.com/astaxie/beego"
)

type IconController struct {
	beego.Controller
}

func (this *IconController) SearchData() {
	users := models.UserData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &users); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = icon.GetSearchModels(users)
	this.ServeJSON()
}

func (this *IconController) InsertData() {
	iicons := models.IIconData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &iicons); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = icon.GetInsertModels(iicons)
	this.ServeJSON()
}
