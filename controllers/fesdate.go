package controllers

import (
	"encoding/json"
	"foodinfoGo/models"
	"foodinfoGo/models/fesdate"

	"github.com/astaxie/beego"
)

type FesdateController struct {
	beego.Controller
}

func (this *FesdateController) SearchData() {
	dform := models.DFormData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &dform); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = fesdate.GetSearchModels(dform)
	this.ServeJSON()
}

func (this *FesdateController) InsertData() {
	iform := models.IFormData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &iform); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = fesdate.GetInsertModels(iform)
	this.ServeJSON()
}
