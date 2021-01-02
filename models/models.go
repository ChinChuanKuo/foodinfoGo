package models

type UserData struct {
	Userid string `json:"userid"`
}

type UserModels struct {
	Newid  string `json:"newid"`
	Status string `json:"status"`
}

type LoginData struct {
	Userid    string `json:"userid"`
	Password  string `json:"password"`
	Longitude string `json:"longitude"`
	Latitude  string `json:"latitude"`
	//Browser   string `json:"browser"`
}

type LoginModels struct {
	Newid   string `json:"newid"`
	Name    string `json:"name"`
	Allname string `json:"allname"`
	Status  string `json:"status"`
}

type OtherData struct {
	Userid string `json:"userid"`
	Values string `json:"values"`
}

type SignupData struct {
	Userid   string `json:"userid"`
	Password string `json:"password"`
	Username string `json:"username"`
	Birthday string `json:"birthday"`
}

type ItemsModels struct {
	Showitem bool                     `json:"showItem"`
	Items    []map[string]interface{} `json:"items"`
	//Items []interface{} `json:"items"`
}

type IIconData struct {
	Items   []map[string]interface{} `json:"items"`
	Qaitems []map[string]interface{} `json:"qaitems"`
	Newid   string                   `json:"newid"`
}

type SSecuModels struct {
	Deviceitems []map[string]interface{} `json:"deviceitems"`
	Status      string                   `json:"status"`
}

type ISecuData struct {
	Externip string `json:"externip"`
	Newid    string `json:"newid"`
}

type SNotiModels struct {
	Generalshow bool   `json:"generalShow"`
	Mixinalshow bool   `json:"mixinalShow"`
	Projectshow bool   `json:"projectShow"`
	Signoutshow bool   `json:"signoutShow"`
	Processshow bool   `json:"processShow"`
	Personsshow bool   `json:"personsShow"`
	Status      string `json:"status"`
}

type INotiData struct {
	Isbool bool   `json:"isbool"`
	Newid  string `json:"newid"`
}

type SRowsData struct {
	Formid string `json:"formId"`
	Value  string `json:"value"`
	Newid  string `json:"newid"`
}

type SRowsModels struct {
	Formid string                   `json:"formId"`
	Tile   string                   `json:"tile"`
	Items  []map[string]interface{} `json:"items"`
	Status string                   `json:"status"`
}

type SFileModels struct {
	File   []byte `json:"file"`
	Status string `json:"status"`
}

type DFormData struct {
	Formid string `json:"formId"`
	Newid  string `json:"newid"`
}

type StatusModels struct {
	Status string `json:"status"`
}

type PermissModels struct {
	Insert bool `json:"insert"`
	Update bool `json:"update"`
	Delete bool `json:"delete"`
	Export bool `json:"export"`
}

type SOptionModels struct {
	Items []map[string]interface{} `json:"items"`
}

type SSiteModels struct {
	Webshow    bool   `json:"webShow"`
	Images     bool   `json:"images"`
	Videos     bool   `json:"videos"`
	Audios     bool   `json:"audios"`
	Src        string `json:"src"`
	Imagepath  string `json:"imagePath"`
	Original   string `json:"original"`
	Encryption string `json:"encryption"`
	Extension  string `json:"extension"`
}

type IItemsData struct {
	Items []map[string]interface{} `json:"items"`
	Newid string                   `json:"newid"`
}

type IFileData struct {
	Formid     string `json:"formId"`
	Original   string `json:"original"`
	Encryption string `json:"encryption"`
	Extension  string `json:"extension"`
	Newid      string `json:"newid"`
}

type SItemModels struct {
	Items  []map[string]interface{} `json:"items"`
	Status string                   `json:"status"`
}

type SItemsModels struct {
	Showitem bool                     `json:"showItem"`
	Items    []map[string]interface{} `json:"items"`
	Status   string                   `json:"status"`
}

type IFormData struct {
	Formid string                   `json:"formId"`
	Tile   string                   `json:"tile"`
	Desc   string                   `json:"desc"`
	Items  []map[string]interface{} `json:"items"`
	Newid  string                   `json:"newid"`
}

type SFormModels struct {
	Formid string `json:"formId"`
	Status string `json:"status"`
}

//in here, is more then models.

type SFormsModels struct {
	Formid  string                   `json:"formId"`
	Tile    string                   `json:"tile"`
	Desc    string                   `json:"desc"`
	Checked bool                     `json:"checked"`
	Items   []map[string]interface{} `json:"items"`
	Status  string                   `json:"status"`
}

type SInfoModels struct {
	Formid  string                   `json:"formId"`
	Tile    string                   `json:"tile"`
	Desc    string                   `json:"desc"`
	Checked bool                     `json:"checked"`
	Heads   []string                 `json:"heads"`
	Items   []map[string]interface{} `json:"items"`
	Status  string                   `json:"status"`
}

type SLocalData struct {
	Longitude string `json:"longitude"`
	Latitude  string `json:"latitude"`
	Length    int    `json:"value"`
	Newid     string `json:"newid"`
}

type PItemModels struct {
	Tile    string                   `json:"tile"`
	Desc    string                   `json:"desc"`
	Checked bool                     `json:"checked"`
	Items   []map[string]interface{} `json:"items"`
}

type SItemData struct {
	Formid    string `json:"formId"`
	Longitude string `json:"longitude"`
	Latitude  string `json:"latitude"`
	Newid     string `json:"newid"`
}
type SPChatData struct {
	Formid string `json:"formId"`
	Length int    `json:"value"`
	Newid  string `json:"newid"`
}
