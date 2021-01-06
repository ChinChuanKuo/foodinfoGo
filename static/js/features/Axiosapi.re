open Axios;
module Form = {
  let checkNew = data => postData("/Form/checkNewData", data);
  let loginForm = data => postData("/Form/loginFormData", data);
  let badgeForm = data =>
    postDatac("/Form/badgeFormData", data, makeConfig(~timeout=30000, ()));
  let permiss = data => postData("/Form/permissData", data);
  let record = data => postData("/Form/recordData", data);
  let badge = data => postData("/Form/badgeData", data);
};

module Login = {
  let checkUser = data => postData("http://localhost:7999/Login/checkUserData", data);
  let loginUser = data => postData("/Login/loginUserData", data);
};

module Forget = {
  let forgetUser = data => postData("/Forget/forgetUserData", data);
};

module Code = {
  let codeUser = data => postData("/Code/codeUserData", data);
};

module Resend = {
  let resendUser = data => postData("/Resend/resendUserData", data);
};

module Signup = {
  let signupUser = data => postData("/Signup/signupUserData", data);
};

module Icon = {
  let search = data => postData("/Icon/searchData", data);
  let insert = data => postData("/Icon/insertData", data);
};

module Option = {
  let add = data => postData("/Option/addData", data);
};

module Files = {
  let upload = formData =>
    postDatac(
      "/Files/uploadData",
      formData,
      makeConfig(
        ~headers=Headers.fromObj({"Content-Type": "multipart/form-data"}),
        (),
      ),
    );
  let website = data => postData("/Files/websiteData", data);
  let download = data => postData("/Files/downloadData", data);
  let transfer = data => postData("/Files/transferData", data);
  let review = data => postData("/Files/reviewData", data);
};

module Default = {
  /*let polling = data =>
    postDatac("/Home/pollingData", data, makeConfig(~timeout=30000, ()));*/
  let polling = data => postData("/Home/pollingData", data);
  let search = data => postData("/Home/searchData", data);
  let scroll = data => postData("/Home/scrollData", data);
  let pingItem = data =>
    postDatac("/Home/pingItemData", data, makeConfig(~timeout=30000, ()));
  //let pingItem = data => postData("/Home/pingItemData", data);
  let sItem = data => postData("/Home/sItemData", data);
  let pingChat = data =>
    postDatac("/Home/pingChatData", data, makeConfig(~timeout=30000, ()));
  //let pingChat = data => postData("/Home/pingChatData", data);
  let sChat = data => postData("/Home/sChatData", data);
  let store = data => postData("/Home/storeData", data);
  let create = data => postData("/Home/createData", data);
};

module Store = {
  let search = data => postData("/Store/searchData", data);
  let insert = data => postData("/Store/insertData", data);
};

module Carte = {
  let search = data => postData("/Carte/searchData", data);
  let addMenu = data => postData("/Carte/addMenuData", data);
  let insert = data => postData("/Carte/insertData", data);
};

module Busdate = {
  let search = data => postData("/Busdate/searchData", data);
  let addWeek = data => postData("/Busdate/addWeekData", data);
  let insert = data => postData("/Busdate/insertData", data);
};

module Fesdate = {
  let search = data => postData("/Fesdate/searchData", data);
  let insert = data => postData("/Fesdate/insertData", data);
};
