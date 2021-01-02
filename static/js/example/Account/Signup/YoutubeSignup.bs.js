// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as React from "react";
import * as ReactIntl from "react-intl";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as Button$BtsCore from "../../../material-ui/core/Button/Button.bs.js";
import * as GridItem$BtsCore from "../../../material-ui/core/Grid/GridItem.bs.js";
import * as AccountBoard$BtsCore from "../AccountBoard.bs.js";
import * as GridContainer$BtsCore from "../../../material-ui/core/Grid/GridContainer.bs.js";
import * as TextFieldOutline$BtsCore from "../../../material-ui/core/TextField/TextFieldOutline.bs.js";

function YoutubeSignup(Props) {
  var error = Props.error;
  var loading = Props.loading;
  var showYoutube = Props.showYoutube;
  var youtubeText = Props.youtubeText;
  var disabled = Props.disabled;
  var userid = Props.userid;
  var changeUserid = Props.changeUserid;
  var keydownUserid = Props.keydownUserid;
  var password = Props.password;
  var changePassword = Props.changePassword;
  var keydownPassword = Props.keydownPassword;
  var username = Props.username;
  var changeUsername = Props.changeUsername;
  var keydownUsername = Props.keydownUsername;
  var birthday = Props.birthday;
  var changeBirthday = Props.changeBirthday;
  var keydownBirthday = Props.keydownBirthday;
  var backForm = Props.backForm;
  var nextForm = Props.nextForm;
  var tmp = {
    right: "0",
    left: "0",
    type_: "email",
    value: userid,
    disabled: disabled,
    children: React.createElement(ReactIntl.FormattedMessage, {
          id: "Login.email",
          defaultMessage: "Email"
        })
  };
  if (changeUserid !== undefined) {
    tmp.onChange = Caml_option.valFromOption(changeUserid);
  }
  if (keydownUserid !== undefined) {
    tmp.onKeyDown = Caml_option.valFromOption(keydownUserid);
  }
  var tmp$1 = {
    right: "0",
    left: "0",
    type_: "password",
    value: password,
    disabled: disabled,
    children: React.createElement(ReactIntl.FormattedMessage, {
          id: "Login.password",
          defaultMessage: "Password"
        })
  };
  if (changePassword !== undefined) {
    tmp$1.onChange = Caml_option.valFromOption(changePassword);
  }
  if (keydownPassword !== undefined) {
    tmp$1.onKeyDown = Caml_option.valFromOption(keydownPassword);
  }
  var tmp$2 = {
    right: "0",
    left: "0",
    value: username,
    disabled: disabled,
    children: React.createElement(ReactIntl.FormattedMessage, {
          id: "Signup.name",
          defaultMessage: "Name"
        })
  };
  if (changeUsername !== undefined) {
    tmp$2.onChange = Caml_option.valFromOption(changeUsername);
  }
  if (keydownUsername !== undefined) {
    tmp$2.onKeyDown = Caml_option.valFromOption(keydownUsername);
  }
  var tmp$3 = {
    right: "0",
    left: "0",
    value: birthday,
    disabled: disabled,
    children: React.createElement(ReactIntl.FormattedMessage, {
          id: "Signup.birthday",
          defaultMessage: "Birthday"
        })
  };
  if (changeBirthday !== undefined) {
    tmp$3.onChange = Caml_option.valFromOption(changeBirthday);
  }
  if (keydownBirthday !== undefined) {
    tmp$3.onKeyDown = Caml_option.valFromOption(keydownBirthday);
  }
  var tmp$4 = {
    variant: "button",
    border: "contained",
    size: "medium",
    disabled: disabled,
    children: React.createElement(ReactIntl.FormattedMessage, {
          id: "Account.back",
          defaultMessage: "Back"
        })
  };
  if (backForm !== undefined) {
    tmp$4.onClick = Caml_option.valFromOption(backForm);
  }
  var tmp$5 = {
    variant: "button",
    border: "contained",
    size: "medium",
    disabled: disabled,
    children: React.createElement(ReactIntl.FormattedMessage, {
          id: "Account.send",
          defaultMessage: "Send"
        })
  };
  if (nextForm !== undefined) {
    tmp$5.onClick = Caml_option.valFromOption(nextForm);
  }
  return React.createElement(AccountBoard$BtsCore.make, {
              error: error,
              loading: loading,
              index: 1,
              tile: "SIGNUP",
              showYoutube: showYoutube,
              youtubeText: youtubeText,
              children: React.createElement(GridContainer$BtsCore.make, {
                    direction: "column",
                    justify: "center",
                    alignItem: "stretch",
                    children: null
                  }, React.createElement(GridItem$BtsCore.make, {
                        right: "0",
                        left: "0",
                        xs: "auto",
                        children: React.createElement(TextFieldOutline$BtsCore.make, tmp)
                      }), React.createElement(GridItem$BtsCore.make, {
                        right: "0",
                        left: "0",
                        xs: "auto",
                        children: React.createElement(TextFieldOutline$BtsCore.make, tmp$1)
                      }), React.createElement(GridItem$BtsCore.make, {
                        right: "0",
                        left: "0",
                        xs: "auto",
                        children: React.createElement(TextFieldOutline$BtsCore.make, tmp$2)
                      }), React.createElement(GridItem$BtsCore.make, {
                        right: "0",
                        left: "0",
                        xs: "auto",
                        children: React.createElement(TextFieldOutline$BtsCore.make, tmp$3)
                      }), React.createElement(GridItem$BtsCore.make, {
                        right: "0",
                        left: "0",
                        xs: "auto",
                        children: React.createElement(GridContainer$BtsCore.make, {
                              direction: "row",
                              justify: "between",
                              alignItem: "center",
                              children: null
                            }, React.createElement(GridItem$BtsCore.make, {
                                  right: "0",
                                  left: "0",
                                  xs: "no",
                                  children: React.createElement(Button$BtsCore.make, tmp$4)
                                }), React.createElement(GridItem$BtsCore.make, {
                                  right: "0",
                                  left: "0",
                                  xs: "no",
                                  children: React.createElement(Button$BtsCore.make, tmp$5)
                                }))
                      }))
            });
}

var make = YoutubeSignup;

export {
  make ,
  
}
/* react Not a pure module */