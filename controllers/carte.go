package controllers

import (
	"encoding/json"
	"foodinfoGo/models"
	"foodinfoGo/models/carte"

	"github.com/astaxie/beego"
)

type CarteController struct {
	beego.Controller
}

func (this *CarteController) SearchData() {
	dform := models.DFormData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &dform); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = carte.GetSearchModels(dform)
	this.ServeJSON()
}

func (this *CarteController) AddMenuData() {
	iitems := models.IItemsData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &iitems); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = carte.GetAddMenuModels(iitems)
	this.ServeJSON()
}

func (this *CarteController) InsertData() {
	iform := models.IFormData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &iform); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = carte.GetInsertModels(iform)
	this.ServeJSON()
}
