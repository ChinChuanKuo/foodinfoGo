package controllers

import (
	"encoding/json"
	"foodinfoGo/models"
	"foodinfoGo/models/store"

	"github.com/astaxie/beego"
)

type StoreController struct {
	beego.Controller
}

func (this *StoreController) SearchData() {
	dform := models.DFormData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &dform); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = store.GetSearchModels(dform)
	this.ServeJSON()
}

func (this *StoreController) InsertData() {
	iform := models.IFormData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &iform); err != nil {
		panic(err.Error())
	}
	this.Data["json"] = store.GetInsertModels(iform)
	this.ServeJSON()
}
