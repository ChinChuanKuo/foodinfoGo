package controllers

import (
	"encoding/json"
	"foodinfoGo/models"
	"foodinfoGo/models/files"
	"path"

	beego "github.com/beego/beego/v2/server/web"
)

type FilesController struct {
	beego.Controller
}

func (this *FilesController) UploadData() {
	file, info, err := this.GetFile("file")
	if err != nil {
		panic(err.Error())
	}
	defer file.Close()
	filepath := "/Users/ChinChuanKuo/Desktop/upload/"
	err = this.SaveToFile("file", path.Join(filepath, info.Filename))
	if err != nil {
		panic(err.Error())
	}
	this.Data["json"] = files.GetUploadModels(filepath, info.Filename)
	this.ServeJSON()
}

func (this *FilesController) WebsiteData() {
	srows := models.SRowsData{}
	if err := json.Unmarshal(this.Ctx.Input.RequestBody, &srows); err != nil {
		panic(err.Error())
	}
	filePath := "/Users/ChinChuanKuo/Desktop/website/"
	this.Data["json"] = files.GetWebsiteModels(srows, filePath)
	this.ServeJSON()
}

func (this *FilesController) DownloadData() {

}

func (this *FilesController) TransferData() {

}

func (this *FilesController) ReviewData() {

}
