// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as List from "bs-platform/lib/es6/list.js";
import * as $$Array from "bs-platform/lib/es6/array.js";
import * as Block from "bs-platform/lib/es6/block.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Tab$BtsCore from "../../material-ui/core/Tabs/Tab.bs.js";
import * as Data$BtsCore from "../../features/Data.bs.js";
import * as Tabs$BtsCore from "../../material-ui/core/Tabs/Tabs.bs.js";
import * as Icons$BtsCore from "../../material-ui/icon/Icons.bs.js";
import * as Status$BtsCore from "../../features/Status.bs.js";
import * as Axiosapi$BtsCore from "../../features/Axiosapi.bs.js";
import * as GridItem$BtsCore from "../../material-ui/core/Grid/GridItem.bs.js";
import * as IconForm$BtsCore from "../../example/Forms/IconForm.bs.js";
import * as Together$BtsCore from "../../styles/Together/Together.bs.js";
import * as IconAction$BtsCore from "../../material-ui/core/IconStyle/IconAction.bs.js";
import * as Navigation$BtsCore from "../../material-ui/core/Navigation/Navigation.bs.js";
import * as NewFacetube$BtsCore from "../../example/Facebook/NewFacetube.bs.js";
import * as GridContainer$BtsCore from "../../material-ui/core/Grid/GridContainer.bs.js";
import * as SnackbarYoutube$BtsCore from "../../material-ui/core/Snackbar/SnackbarYoutube.bs.js";
import * as BottomNavigation$BtsCore from "../../example/BottomNavigation/BottomNavigation.bs.js";

((require('../../../scss/pages/Together/together.scss')));

function reducer(state, action) {
  if (typeof action === "number") {
    switch (action) {
      case /* SettingError */0 :
          return {
                  formLoad: state.formLoad,
                  showProgress: state.showProgress,
                  error: !state.error,
                  items: state.items,
                  qaitems: state.qaitems,
                  tabitems: state.tabitems,
                  index: state.index,
                  bottomitems: state.bottomitems,
                  showYoutube: state.showYoutube,
                  youtubeText: state.youtubeText
                };
      case /* SettingFormLoad */1 :
          return {
                  formLoad: !state.formLoad,
                  showProgress: state.showProgress,
                  error: state.error,
                  items: state.items,
                  qaitems: state.qaitems,
                  tabitems: state.tabitems,
                  index: state.index,
                  bottomitems: state.bottomitems,
                  showYoutube: state.showYoutube,
                  youtubeText: state.youtubeText
                };
      case /* ActionShowProgress */2 :
          return {
                  formLoad: state.formLoad,
                  showProgress: !state.showProgress,
                  error: state.error,
                  items: state.items,
                  qaitems: state.qaitems,
                  tabitems: state.tabitems,
                  index: state.index,
                  bottomitems: state.bottomitems,
                  showYoutube: state.showYoutube,
                  youtubeText: state.youtubeText
                };
      
    }
  } else {
    switch (action.tag | 0) {
      case /* ClickItemTab */0 :
          var index = action[0];
          return {
                  formLoad: state.formLoad,
                  showProgress: state.showProgress,
                  error: state.error,
                  items: state.items,
                  qaitems: state.qaitems,
                  tabitems: List.mapi((function (i, tabitem) {
                          return {
                                  showTab: index === i,
                                  tabImage: tabitem.tabImage
                                };
                        }), state.tabitems),
                  index: index,
                  bottomitems: state.bottomitems,
                  showYoutube: state.showYoutube,
                  youtubeText: state.youtubeText
                };
      case /* ClickBottomNavigation */1 :
          var index$1 = action[0];
          return {
                  formLoad: state.formLoad,
                  showProgress: state.showProgress,
                  error: state.error,
                  items: state.items,
                  qaitems: state.qaitems,
                  tabitems: state.tabitems,
                  index: state.index,
                  bottomitems: List.mapi((function (i, item) {
                          return {
                                  showAction: index$1 === i,
                                  icon: item.icon,
                                  tile: item.tile
                                };
                        }), state.bottomitems),
                  showYoutube: state.showYoutube,
                  youtubeText: state.youtubeText
                };
      case /* ActionSnackBar */2 :
          return {
                  formLoad: state.formLoad,
                  showProgress: state.showProgress,
                  error: state.error,
                  items: state.items,
                  qaitems: state.qaitems,
                  tabitems: state.tabitems,
                  index: state.index,
                  bottomitems: state.bottomitems,
                  showYoutube: action[1],
                  youtubeText: action[0]
                };
      
    }
  }
}

var initialState_items = [
  {
    icon: Icons$BtsCore.addBlack,
    value: "add"
  },
  {
    icon: Icons$BtsCore.arrowUpBlack,
    value: "arrowUp"
  },
  {
    icon: Icons$BtsCore.assistantBlack,
    value: "assistant"
  },
  {
    icon: Icons$BtsCore.arrowDownBlack,
    value: "arrowDown"
  },
  {
    icon: Icons$BtsCore.attachFileBlack,
    value: "attachFile"
  },
  {
    icon: Icons$BtsCore.accesstimeBlack,
    value: "accesstime"
  },
  {
    icon: Icons$BtsCore.accountBoxBlack,
    value: "accountBox"
  },
  {
    icon: Icons$BtsCore.accountTreeBlack,
    value: "accountTree"
  },
  {
    icon: Icons$BtsCore.announcementBlack,
    value: "announcement"
  },
  {
    icon: Icons$BtsCore.arrowBackIosBlack,
    value: "arrowBackIos"
  },
  {
    icon: Icons$BtsCore.accountCircleBlack,
    value: "accountCircle"
  },
  {
    icon: Icons$BtsCore.assignmentIndBlack,
    value: "assignmentInd"
  },
  {
    icon: Icons$BtsCore.arrowForwardIosBlack,
    value: "arrowForwardIos"
  },
  {
    icon: Icons$BtsCore.bookBlack,
    value: "book"
  },
  {
    icon: Icons$BtsCore.barChartBlack,
    value: "barChart"
  },
  {
    icon: Icons$BtsCore.brightness4Black,
    value: "brightness4"
  },
  {
    icon: Icons$BtsCore.brightnessLowBlack,
    value: "brightnessLow"
  },
  {
    icon: Icons$BtsCore.brightnessHighBlack,
    value: "brightnessHigh"
  },
  {
    icon: Icons$BtsCore.bookmarkBorderBlack,
    value: "bookmarkBorder"
  },
  {
    icon: Icons$BtsCore.cancelBlack,
    value: "cancel"
  },
  {
    icon: Icons$BtsCore.clearBlack,
    value: "clear"
  },
  {
    icon: Icons$BtsCore.createBlack,
    value: "create"
  },
  {
    icon: Icons$BtsCore.cachedBlack,
    value: "cached"
  },
  {
    icon: Icons$BtsCore.checkBoxBlack,
    value: "checkBox"
  },
  {
    icon: Icons$BtsCore.colorLensBlack,
    value: "colorLens"
  },
  {
    icon: Icons$BtsCore.cardTravelBlack,
    value: "cardTravel"
  },
  {
    icon: Icons$BtsCore.chatBubbleBlack,
    value: "chatBubble"
  },
  {
    icon: Icons$BtsCore.collectionsBlack,
    value: "collections"
  },
  {
    icon: Icons$BtsCore.cloudDownloadBlack,
    value: "cloudDownload"
  },
  {
    icon: Icons$BtsCore.checkBoxOutlineBlankBlack,
    value: "checkBoxOutlineBlank"
  },
  {
    icon: Icons$BtsCore.doneBlack,
    value: "done"
  },
  {
    icon: Icons$BtsCore.deleteBlack,
    value: "delete"
  },
  {
    icon: Icons$BtsCore.dateRangeBlack,
    value: "dateRange"
  },
  {
    icon: Icons$BtsCore.descriptionBlack,
    value: "description"
  },
  {
    icon: Icons$BtsCore.editBlack,
    value: "edit"
  },
  {
    icon: Icons$BtsCore.emailBlack,
    value: "email"
  },
  {
    icon: Icons$BtsCore.eventBlack,
    value: "event"
  },
  {
    icon: Icons$BtsCore.errorBlack,
    value: "error"
  },
  {
    icon: Icons$BtsCore.exploreBlack,
    value: "explore"
  },
  {
    icon: Icons$BtsCore.flagBlack,
    value: "flag"
  },
  {
    icon: Icons$BtsCore.factoryBlack,
    value: "factory"
  },
  {
    icon: Icons$BtsCore.fileCopyBlack,
    value: "fileCopy"
  },
  {
    icon: Icons$BtsCore.formatBoldBlack,
    value: "formatBold"
  },
  {
    icon: Icons$BtsCore.formatSizeBlack,
    value: "formatSize"
  },
  {
    icon: Icons$BtsCore.formatClearBlack,
    value: "formatClear"
  },
  {
    icon: Icons$BtsCore.formatItalicBlack,
    value: "formatItalic"
  },
  {
    icon: Icons$BtsCore.favoriteBorderBlack,
    value: "favoriteBorder"
  },
  {
    icon: Icons$BtsCore.formatUnderlinedBlack,
    value: "formatUnderlined"
  },
  {
    icon: Icons$BtsCore.formatAlignLeftBlack,
    value: "formatAlignLeft"
  },
  {
    icon: Icons$BtsCore.formatAlignRightBlack,
    value: "formatAlignRight"
  },
  {
    icon: Icons$BtsCore.formatAlignCenterBlack,
    value: "formatAlignCenter"
  },
  {
    icon: Icons$BtsCore.formatListBulletedBlack,
    value: "formatListBulleted"
  },
  {
    icon: Icons$BtsCore.formatListNumberedBlack,
    value: "formatListNumbered"
  },
  {
    icon: Icons$BtsCore.formatIndentDecreaseBlack,
    value: "formatIndentDecrease"
  },
  {
    icon: Icons$BtsCore.formatIndentIncreaseBlack,
    value: "formatIndentIncrease"
  },
  {
    icon: Icons$BtsCore.groupBlack,
    value: "group"
  },
  {
    icon: Icons$BtsCore.homeBlack,
    value: "home"
  },
  {
    icon: Icons$BtsCore.helpBlack,
    value: "help"
  },
  {
    icon: Icons$BtsCore.helpOutlineBlack,
    value: "helpOutline"
  },
  {
    icon: Icons$BtsCore.imageBlack,
    value: "image"
  },
  {
    icon: Icons$BtsCore.inputBlack,
    value: "input"
  },
  {
    icon: Icons$BtsCore.importExportBlack,
    value: "importExport"
  },
  {
    icon: Icons$BtsCore.importContactsBlack,
    value: "importContacts"
  },
  {
    icon: Icons$BtsCore.insertInvitationBlack,
    value: "insertInvitation"
  },
  {
    icon: Icons$BtsCore.keyboardBlack,
    value: "keyboardBlack"
  },
  {
    icon: Icons$BtsCore.keyboardBackspaceBlack,
    value: "keyboardBackspace"
  },
  {
    icon: Icons$BtsCore.keyboardArrowRightBlack,
    value: "keyboardArrowRight"
  },
  {
    icon: Icons$BtsCore.listBlack,
    value: "list"
  },
  {
    icon: Icons$BtsCore.lockBlack,
    value: "lock"
  },
  {
    icon: Icons$BtsCore.languageBlack,
    value: "language"
  },
  {
    icon: Icons$BtsCore.libraryBooksBlack,
    value: "libraryBooks"
  },
  {
    icon: Icons$BtsCore.localActivityBlack,
    value: "localActivity"
  },
  {
    icon: Icons$BtsCore.mapBlack,
    value: "map"
  },
  {
    icon: Icons$BtsCore.mailBlack,
    value: "mail"
  },
  {
    icon: Icons$BtsCore.menuBlack,
    value: "menu"
  },
  {
    icon: Icons$BtsCore.menuBookBlack,
    value: "menuBook"
  },
  {
    icon: Icons$BtsCore.moreVertBlack,
    value: "moreVert"
  },
  {
    icon: Icons$BtsCore.monetizationOnBlack,
    value: "monetizationOn"
  },
  {
    icon: Icons$BtsCore.noteBlack,
    value: "note"
  },
  {
    icon: Icons$BtsCore.notesBlack,
    value: "notes"
  },
  {
    icon: Icons$BtsCore.nightsStayBlack,
    value: "nightsStay"
  },
  {
    icon: Icons$BtsCore.notificationsBlack,
    value: "notifications"
  },
  {
    icon: Icons$BtsCore.notificationsActiveBlack,
    value: "notificationsActive"
  },
  {
    icon: Icons$BtsCore.notificationImportantBlack,
    value: "notificationImportant"
  },
  {
    icon: Icons$BtsCore.photoBlack,
    value: "photo"
  },
  {
    icon: Icons$BtsCore.personBlack,
    value: "person"
  },
  {
    icon: Icons$BtsCore.peopleBlack,
    value: "people"
  },
  {
    icon: Icons$BtsCore.personAddBlack,
    value: "personAdd"
  },
  {
    icon: Icons$BtsCore.privacyTipBlack,
    value: "privacyTip"
  },
  {
    icon: Icons$BtsCore.questionAnswerBlack,
    value: "questionAnswer"
  },
  {
    icon: Icons$BtsCore.redoBlack,
    value: "redo"
  },
  {
    icon: Icons$BtsCore.restoreBlack,
    value: "restore"
  },
  {
    icon: Icons$BtsCore.refreshBlack,
    value: "refresh"
  },
  {
    icon: Icons$BtsCore.radioButtonCheckedBlack,
    value: "radioButtonChecked"
  },
  {
    icon: Icons$BtsCore.radioButtonUncheckedBlack,
    value: "radioButtonUnchecked"
  },
  {
    icon: Icons$BtsCore.sendBlack,
    value: "send"
  },
  {
    icon: Icons$BtsCore.saveBlack,
    value: "save"
  },
  {
    icon: Icons$BtsCore.storeBlack,
    value: "store"
  },
  {
    icon: Icons$BtsCore.shareBlack,
    value: "share"
  },
  {
    icon: Icons$BtsCore.searchBlack,
    value: "search"
  },
  {
    icon: Icons$BtsCore.settingsBlack,
    value: "settings"
  },
  {
    icon: Icons$BtsCore.storefrontBlack,
    value: "storefront"
  },
  {
    icon: Icons$BtsCore.securityBlack,
    value: "security"
  },
  {
    icon: Icons$BtsCore.shortTextBlack,
    value: "shortText"
  },
  {
    icon: Icons$BtsCore.strikethroughSBlack,
    value: "strikethroughS"
  },
  {
    icon: Icons$BtsCore.settingsApplicationsBlack,
    value: "settingsApplications"
  },
  {
    icon: Icons$BtsCore.tourBlack,
    value: "tour"
  },
  {
    icon: Icons$BtsCore.todayBlack,
    value: "today"
  },
  {
    icon: Icons$BtsCore.translateBlack,
    value: "translate"
  },
  {
    icon: Icons$BtsCore.textFormatBlack,
    value: "textFormat"
  },
  {
    icon: Icons$BtsCore.textFieldsBlack,
    value: "textFields"
  },
  {
    icon: Icons$BtsCore.transmissionBlack,
    value: "transmission"
  },
  {
    icon: Icons$BtsCore.undoBlack,
    value: "undo"
  },
  {
    icon: Icons$BtsCore.wifiBlack,
    value: "wifi"
  },
  {
    icon: Icons$BtsCore.wifiOffBlack,
    value: "wifiOff"
  }
];

var initialState_qaitems = [
  {
    icon: Icons$BtsCore.shortTextBlack,
    value: "text"
  },
  {
    icon: Icons$BtsCore.notesBlack,
    value: "textarea"
  },
  {
    icon: Icons$BtsCore.menuBlack,
    value: "textline"
  },
  {
    icon: Icons$BtsCore.radioButtonCheckedBlack,
    value: "radio"
  },
  {
    icon: Icons$BtsCore.checkBoxBlack,
    value: "checkbox"
  },
  {
    icon: Icons$BtsCore.arrowDownBlack,
    value: "droplist"
  },
  {
    icon: Icons$BtsCore.imageBlack,
    value: "image"
  },
  {
    icon: Icons$BtsCore.collectionsBlack,
    value: "collections"
  }
];

var initialState_tabitems = /* :: */[
  {
    showTab: true,
    tabImage: Icons$BtsCore.homeBlack
  },
  /* :: */[
    {
      showTab: false,
      tabImage: Icons$BtsCore.homeBlack
    },
    /* [] */0
  ]
];

var initialState_bottomitems = /* :: */[
  {
    showAction: true,
    icon: Icons$BtsCore.settingsApplicationsBlack,
    tile: "Settings"
  },
  /* :: */[
    {
      showAction: true,
      icon: Icons$BtsCore.saveBlack,
      tile: "Save"
    },
    /* [] */0
  ]
];

var initialState = {
  formLoad: false,
  showProgress: true,
  error: false,
  items: initialState_items,
  qaitems: initialState_qaitems,
  tabitems: initialState_tabitems,
  index: 0,
  bottomitems: initialState_bottomitems,
  showYoutube: false,
  youtubeText: ""
};

function Icon(Props) {
  var match = React.useReducer(reducer, initialState);
  var dispatch = match[1];
  var state = match[0];
  var barShowRestoreAction = function (youtubeText) {
    Curry._1(dispatch, /* ActionSnackBar */Block.__(2, [
            youtubeText,
            true
          ]));
    setTimeout((function (param) {
            return Curry._1(dispatch, /* ActionSnackBar */Block.__(2, [
                          "",
                          false
                        ]));
          }), 5000);
    
  };
  var searchAJax = function (param) {
    Axiosapi$BtsCore.Icon.search(Data$BtsCore.userData(localStorage.getItem("newid"))).then((function (response) {
              var match = response.data.status;
              var tmp;
              if (match === "istrue") {
                tmp = Curry._1(dispatch, /* ActionShowProgress */2);
              } else {
                Curry._1(dispatch, /* SettingError */0);
                barShowRestoreAction(Status$BtsCore.statusModule(response.data.status));
                tmp = Curry._1(dispatch, /* ActionShowProgress */2);
              }
              return Promise.resolve(tmp);
            })).catch((function (error) {
            return Promise.resolve((console.log(error), undefined));
          }));
    
  };
  React.useEffect((function () {
          if (state.formLoad) {
            return (function (param) {
                      console.log("action");
                      
                    });
          }
          Curry._1(dispatch, /* SettingFormLoad */1);
          var timeId = searchAJax(undefined);
          return (function (param) {
                    return timeId;
                  });
        }));
  var clickItemTab = React.useCallback((function (i) {
          return Curry._1(dispatch, /* ClickItemTab */Block.__(0, [i]));
        }));
  var clickBottomNavigation = React.useCallback((function (bi) {
          if (bi === 0) {
            Curry._1(dispatch, /* ActionShowProgress */2);
            return Curry._1(dispatch, /* ActionShowProgress */2);
          } else if (bi === 1) {
            Curry._1(dispatch, /* ActionShowProgress */2);
            Axiosapi$BtsCore.Icon.insert(Data$BtsCore.iIconData(state.items, state.qaitems, localStorage.getItem("newid"))).then((function (response) {
                      return Promise.resolve((barShowRestoreAction(Status$BtsCore.statusModule(response.data.status)), Curry._1(dispatch, /* ActionShowProgress */2)));
                    })).catch((function (error) {
                    return Promise.resolve((console.log(error), undefined));
                  }));
            return ;
          } else {
            return ;
          }
        }));
  var match$1 = state.index;
  return React.createElement(React.Fragment, undefined, React.createElement(NewFacetube$BtsCore.make, {
                  showProgress: state.showProgress,
                  error: state.error,
                  width: "100",
                  bottom: "56",
                  children: React.createElement(GridContainer$BtsCore.make, {
                        direction: "column",
                        justify: "center",
                        alignItem: "stretch",
                        children: null
                      }, React.createElement(GridItem$BtsCore.make, {
                            style: {
                              position: "sticky",
                              top: "0px",
                              zIndex: "1000"
                            },
                            top: "0",
                            right: "30",
                            bottom: "0",
                            left: "30",
                            xs: "auto",
                            children: React.createElement(Tabs$BtsCore.make, {
                                  id: "icon-",
                                  index: state.index,
                                  short: 20,
                                  height: "3",
                                  children: $$Array.of_list(List.mapi((function (i, tabitem) {
                                              return React.createElement(Tab$BtsCore.make, {
                                                          showTab: tabitem.showTab,
                                                          maxWidth: "111.6",
                                                          borderRadius: "15",
                                                          id: "icon-" + String(i),
                                                          animationName: "none",
                                                          onClick: (function (param) {
                                                              return Curry._1(clickItemTab, i);
                                                            }),
                                                          children: React.createElement(IconAction$BtsCore.make, {
                                                                animation: "leftRight",
                                                                src: tabitem.tabImage
                                                              })
                                                        });
                                            }), state.tabitems))
                                })
                          }), React.createElement(GridItem$BtsCore.make, {
                            top: "0",
                            right: "0",
                            bottom: "0",
                            left: "0",
                            xs: "auto",
                            children: match$1 !== 0 ? React.createElement(IconForm$BtsCore.make, {
                                    items: state.qaitems
                                  }) : React.createElement(IconForm$BtsCore.make, {
                                    items: state.items
                                  })
                          }))
                }), state.error ? null : React.createElement(Navigation$BtsCore.make, {
                    style: Object.assign(({}), Together$BtsCore.marginAuto, {
                          bottom: "0",
                          left: "0",
                          maxWidth: "770px",
                          position: "fixed",
                          right: "0",
                          transition: "left 195ms cubic-bezier(0.4, 0, 0.6, 1) 0ms"
                        }),
                    className: "facetubenavigation",
                    children: $$Array.of_list(List.mapi((function (bi, bottomitem) {
                                return React.createElement(BottomNavigation$BtsCore.make, {
                                            showAction: bottomitem.showAction,
                                            disabled: state.showProgress,
                                            onClick: (function (param) {
                                                return Curry._1(clickBottomNavigation, bi);
                                              }),
                                            icon: bottomitem.icon,
                                            tile: bottomitem.tile
                                          });
                              }), state.bottomitems))
                  }), React.createElement(SnackbarYoutube$BtsCore.make, {
                  showYoutube: state.showYoutube,
                  position: "bottomLeft",
                  children: /* tuple */[
                    React.createElement("span", undefined, state.youtubeText),
                    null
                  ]
                }));
}

var make = Icon;

export {
  reducer ,
  initialState ,
  make ,
  
}
/*  Not a pure module */