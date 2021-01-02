package controllers

import (
	"encoding/json"
	"foodinfoGo/models"
	"foodinfoGo/models/busdate"

	"github.com/astaxie/beego"
)

type BusdateController struct {
	beego.Controller
}

func (this *BusdateController) SearchData() {
	dform := models.DFormData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &dform); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = busdate.GetSearchModels(dform)
	this.ServeJSON()
}

func (this *BusdateController) AddWeekData() {
	iitems := models.IItemsData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &iitems); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = busdate.GetAddWeekModels(iitems)
	this.ServeJSON()
}

func (this *BusdateController) InsertData() {
	iform := models.IFormData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &iform); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = busdate.GetInsertModels(iform)
	this.ServeJSON()
}
