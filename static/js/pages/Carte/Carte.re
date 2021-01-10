open React;
open Together;
open ReactIntl;
open Icons;
open Path;
open Data;
open Items;
open Axiosapi;
open Storage;
open SwitchColor;
open IconAnimation;
[%bs.raw {|require('../../../scss/pages/Together/together.scss')|}];

type item = {
  muId: int,
  nameId: int,
  showName: bool,
  nameOutValue: string,
  nameChecked: bool,
  showNameDrop: bool,
  showNameFile: bool,
  nameTitle: string,
  nameValue: string,
  showNameMenu: bool,
  nameitems: array(optionitem),
  priceId: int,
  showPrice: bool,
  priceOutValue: string,
  priceChecked: bool,
  showPriceDrop: bool,
  showPriceFile: bool,
  priceTitle: string,
  priceValue: string,
  showPriceMenu: bool,
  priceitems: array(optionitem),
  allergyId: int,
  showAllergy: bool,
  allergyOutValue: string,
  allergyChecked: bool,
  showAllergyDrop: bool,
  showAllergyFile: bool,
  allergyTitle: string,
  allergyValue: string,
  showAllergyMenu: bool,
  allergyitems: array(optionitem),
  albumId: int,
  showAlbum: bool,
  albumOutValue: string,
  albumChecked: bool,
  showAlbumDrop: bool,
  showAlbumFile: bool,
  albumTitle: string,
  albumValue: string,
  showAlbumMenu: bool,
  albumitems: array(optionitem),
  remarkId: int,
  showRemark: bool,
  remarkOutValue: string,
  remarkChecked: bool,
  showRemarkDrop: bool,
  showRemarkFile: bool,
  remarkTitle: string,
  remarkValue: string,
  showRemarkMenu: bool,
  remarkitems: array(optionitem),
  showMore: bool,
  itemDelete: bool,
  itemModify: bool,
  itemCreate: bool,
};

type state = {
  formLoad: bool,
  formWidth: int,
  formHeight: int,
  showProgress: bool,
  error: bool,
  badge: string,
  insert: bool,
  update: bool,
  delete: bool,
  export: bool,
  formId: string,
  tile: string,
  desc: string,
  checked: bool,
  tabitems: list(tabtitem),
  index: int,
  showItem: bool,
  items: array(item),
  showYoutube: bool,
  youtubeText: string,
};

type action =
  | SettingError
  | SettingFormLoad(string)
  | SettingFormWidth(int, int)
  | ActionShowProgress
  | ActionBadgeItems(string)
  | ActionPermissItems(bool, bool, bool, bool)
  | SettingFormItems(string, string, bool, array(item))
  | ChangeFormTitle(string)
  | ChangeFormDescription(string)
  | ShowChecked
  | ClickItemTab(int)
  | ShowNameDrop(bool, int)
  | ShowNameFile(string, int)
  | ChangeItemName(string, int)
  | ShowNameMenu(int)
  | ClickNameMenu(string, int)
  | ShowPriceDrop(bool, int)
  | ShowPriceFile(string, int)
  | ChangeItemPrice(string, int)
  | ShowPriceMenu(int)
  | ClickPriceMenu(string, int)
  | ShowAllergyDrop(bool, int)
  | ShowAllergyFile(string, int)
  | ChangeItemAllergy(string, int)
  | ShowAllergyMenu(int)
  | ClickAllergyMenu(string, int)
  | ShowAlbumDrop(bool, int)
  | ShowAlbumFile(string, int)
  | ChangeItemAlbum(string, int)
  | ShowAlbumMenu(int)
  | ClickAlbumMenu(string, int)
  | ShowRemarkDrop(bool, int)
  | ShowRemarkFile(string, int)
  | ChangeItemRemark(string, int)
  | ShowRemarkMenu(int)
  | ClickRemarkMenu(string, int)
  | ShowMenuForm(int)
  | DeleteMenuForm(int)
  | RefreshMenuForm
  | AddMenuForm(array(item))
  | ActionSnackBar(string, bool);

let reducer = (state, action) =>
  switch (action) {
  | SettingError => {...state, error: !state.error}
  | SettingFormLoad(value) => {
      ...state,
      formId: value,
      formLoad: !state.formLoad,
    }
  | SettingFormWidth(width, height) => {
      ...state,
      formWidth: width,
      formHeight: height,
    }
  | ActionShowProgress => {...state, showProgress: !state.showProgress}
  | ActionBadgeItems(badge) => {...state, badge}
  | ActionPermissItems(insert, update, delete, export) => {
      ...state,
      insert,
      update,
      delete,
      export,
    }
  | SettingFormItems(tile, desc, checked, items) => {
      ...state,
      tile,
      desc,
      checked,
      items,
      showItem: true,
    }
  | ChangeFormTitle(value) => {...state, tile: value}
  | ChangeFormDescription(value) => {...state, desc: value}
  | ShowChecked => {...state, checked: !state.checked}
  | ClickItemTab(index) => {
      ...state,
      tabitems:
        List.mapi(
          (i, tabtitem) => {...tabtitem, showTabt: index == i},
          state.tabitems,
        ),
      index,
    }
  | ShowNameDrop(droped, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, showNameDrop: droped} : item,
          state.items,
        ),
    }
  | ShowNameFile(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                nameValue: value,
                showNameFile: !item.showNameFile,
                itemModify: true,
              }
              : item,
          state.items,
        ),
    }
  | ChangeItemName(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, nameValue: value, itemModify: true} : item,
          state.items,
        ),
    }
  | ShowNameMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showNameMenu: !item.showNameMenu} : item,
          state.items,
        ),
    }
  | ClickNameMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                nameValue: value,
                showNameMenu: !item.showNameMenu,
                itemModify: true,
              }
              : item,
          state.items,
        ),
    }
  | ShowPriceDrop(droped, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, showPriceDrop: droped} : item,
          state.items,
        ),
    }
  | ShowPriceFile(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                priceValue: value,
                showPriceFile: !item.showPriceFile,
                itemModify: true,
              }
              : item,
          state.items,
        ),
    }
  | ChangeItemPrice(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, priceValue: value, itemModify: true} : item,
          state.items,
        ),
    }
  | ShowPriceMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showPriceMenu: !item.showPriceMenu} : item,
          state.items,
        ),
    }
  | ClickPriceMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                priceValue: value,
                showPriceMenu: !item.showPriceMenu,
                itemModify: true,
              }
              : item,
          state.items,
        ),
    }
  | ShowAllergyDrop(droped, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showAllergyDrop: droped} : item,
          state.items,
        ),
    }
  | ShowAllergyFile(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                allergyValue: value,
                showAllergyFile: !item.showAllergyFile,
                itemModify: true,
              }
              : item,
          state.items,
        ),
    }
  | ChangeItemAllergy(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, allergyValue: value, itemModify: true} : item,
          state.items,
        ),
    }
  | ShowAllergyMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, showAllergyMenu: !item.showAllergyMenu} : item,
          state.items,
        ),
    }
  | ClickAllergyMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                allergyValue: value,
                showAllergyMenu: !item.showAllergyMenu,
                itemModify: true,
              }
              : item,
          state.items,
        ),
    }
  | ShowAlbumDrop(droped, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, showAlbumDrop: droped} : item,
          state.items,
        ),
    }
  | ShowAlbumFile(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                albumValue: value,
                showAlbumFile: !item.showAlbumFile,
                itemModify: true,
              }
              : item,
          state.items,
        ),
    }
  | ChangeItemAlbum(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, albumValue: value, itemModify: true} : item,
          state.items,
        ),
    }
  | ShowAlbumMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showAlbumMenu: !item.showAlbumMenu} : item,
          state.items,
        ),
    }
  | ClickAlbumMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                albumValue: value,
                showAlbumMenu: !item.showAlbumMenu,
                itemModify: true,
              }
              : item,
          state.items,
        ),
    }
  | ShowRemarkDrop(droped, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, showRemarkDrop: droped} : item,
          state.items,
        ),
    }
  | ShowRemarkFile(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                remarkValue: value,
                showRemarkFile: !item.showRemarkFile,
                itemModify: true,
              }
              : item,
          state.items,
        ),
    }
  | ChangeItemRemark(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, remarkValue: value, itemModify: true} : item,
          state.items,
        ),
    }
  | ShowRemarkMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, showRemarkMenu: !item.showRemarkMenu} : item,
          state.items,
        ),
    }
  | ClickRemarkMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                remarkValue: value,
                showRemarkMenu: !item.showRemarkMenu,
                itemModify: true,
              }
              : item,
          state.items,
        ),
    }
  | ShowMenuForm(mindex) => {
      ...state,
      items:
        Array.mapi(
          (mi, item) =>
            mindex == mi ? {...item, showMore: !item.showMore} : item,
          state.items,
        ),
    }
  | DeleteMenuForm(mindex) => {
      ...state,
      items:
        Array.mapi(
          (mi, item) =>
            mindex == mi ? {...item, itemDelete: !item.itemDelete} : item,
          state.items,
        ),
    }
  | RefreshMenuForm => {
      ...state,
      items:
        Js_array.filter(
          (item: item) => item.itemDelete !== true,
          state.items,
        ),
    }
  | AddMenuForm(items) => {
      ...state,
      items: Array.append(state.items, items),
    }
  | ActionSnackBar(youtubeText, showYoutube) => {
      ...state,
      youtubeText,
      showYoutube,
    }
  };

let initialState = {
  formLoad: false,
  formWidth: 0,
  formHeight: 0,
  showProgress: true,
  error: false,
  badge: "",
  insert: false,
  update: false,
  delete: false,
  export: false,
  formId: "",
  tabitems: [
    {showTabt: false, tabImage: storeBlack, tabPath: storePath},
    {showTabt: false, tabImage: menuBookBlack, tabPath: cartePath},
    {showTabt: true, tabImage: todayBlack, tabPath: busdatePath},
    {showTabt: false, tabImage: insertInvitationBlack, tabPath: fesdatePath},
  ],
  index: 1,
  tile: "",
  desc: "",
  checked: false,
  showItem: false,
  items: [||],
  showYoutube: false,
  youtubeText: "",
};

[@react.component]
let make = _ => {
  let (state, dispatch) = useReducer(reducer, initialState);
  let maxHeight = string_of_int(state.formHeight - 365) ++ "px";

  let fileRef = useRef(Js.Nullable.null);

  let barShowRestoreAction = youtubeText => {
    ActionSnackBar(youtubeText, true) |> dispatch;
    Js.Global.setTimeout(() => ActionSnackBar("", false) |> dispatch, 5000)
    |> ignore;
  };

  let searchAJax = formId =>
    Js.Promise.(
      dFormData(formId, "newid" |> Locals.select)
      |> Axiosapi.Carte.search
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               SettingFormItems(
                 response##data##tile,
                 response##data##desc,
                 response##data##checked,
                 response##data##items,
               )
               |> dispatch;
               ActionShowProgress |> dispatch;
             | _ =>
               SettingError |> dispatch;
               response##data##status
               |> Status.statusModule
               |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             }
           )
           |> resolve
         })
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let permissAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> userData
      |> Form.permiss
      |> then_(response =>
           {
             ActionPermissItems(
               response##data##insert,
               response##data##update,
               response##data##delete,
               response##data##export,
             )
             |> dispatch;
             ReasonReactRouter.dangerouslyGetInitialUrl().hash |> searchAJax;
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  useEffect(() =>
    if (state.formLoad) {
      Some(() => "action" |> Js.log);
    } else {
      let testtime =
        SettingFormLoad(ReasonReactRouter.dangerouslyGetInitialUrl().hash)
        |> dispatch;
      let sizeId =
        SettingFormWidth(Window.Sizes.width, Window.Sizes.height) |> dispatch;
      let timeId = permissAJax();
      Some(
        () => {
          testtime;
          sizeId;
          timeId;
        },
      );
    }
  );

  let handleResize = event =>
    SettingFormWidth(
      event##currentTarget##innerWidth,
      event##currentTarget##innerHeight,
    )
    |> dispatch;

  useEffect0(() => {
    let watcherId =
      ReasonReactRouter.watchUrl(url => {
        SettingFormLoad(ReasonReactRouter.dangerouslyGetInitialUrl().hash)
        |> dispatch;
        ActionShowProgress |> dispatch;
      });
    let sizeId = Window.Listeners.add("resize", handleResize, true) |> ignore;
    Some(
      () => {
        ReasonReactRouter.unwatchUrl(watcherId);
        sizeId;
      },
    );
  });

  let changeFormTitle =
    useCallback(value => ChangeFormTitle(value) |> dispatch);

  let changeFormDescription =
    useCallback(value => ChangeFormDescription(value) |> dispatch);

  let showChecked = useCallback(_ => ShowChecked |> dispatch);

  let clickItemTab =
    useCallback((i, tabPath) => {
      ClickItemTab(i) |> dispatch;
      tabPath ++ "#" ++ state.formId |> ReasonReactRouter.push;
    });

  let upNameAJax = (file, i) => {
    let formData = FormData.make();
    FormData.append(formData, "file", file) |> ignore;
    Js.Promise.(
      formData
      |> Files.upload
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               ShowNameFile(response##data##file, i) |> dispatch;
               ActionShowProgress |> dispatch;
             | _ =>
               response##data##status
               |> Status.uploadModels
               |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             }
           )
           |> resolve
         })
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );
  };

  let dragOverName =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowNameDrop(true, i) |> dispatch;
    });

  let dragLeaveName =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowNameDrop(false, i) |> dispatch;
    });

  let dropItemName =
    useCallback((event, value, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ActionShowProgress |> dispatch;
      ShowNameDrop(false, i) |> dispatch;
      i |> upNameAJax(value);
    });

  let uploadItemName =
    useCallback((value, i) => {
      ActionShowProgress |> dispatch;
      i |> upNameAJax(value);
    });

  let changeItemName =
    useCallback((value, i) => ChangeItemName(value, i) |> dispatch);

  let showNameMenu = useCallback(i => ShowNameMenu(i) |> dispatch);

  let clickNameMenu =
    useCallback((value, i) => ClickNameMenu(value, i) |> dispatch);

  let upPriceAJax = (file, i) => {
    let formData = FormData.make();
    FormData.append(formData, "file", file) |> ignore;
    Js.Promise.(
      formData
      |> Files.upload
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               ShowPriceFile(response##data##file, i) |> dispatch;
               ActionShowProgress |> dispatch;
             | _ =>
               response##data##status
               |> Status.uploadModels
               |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             }
           )
           |> resolve
         })
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );
  };

  let dragOverPrice =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowPriceDrop(true, i) |> dispatch;
    });

  let dragLeavePrice =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowPriceDrop(false, i) |> dispatch;
    });

  let dropItemPrice =
    useCallback((event, value, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ActionShowProgress |> dispatch;
      ShowPriceDrop(false, i) |> dispatch;
      i |> upPriceAJax(value);
    });

  let uploadItemPrice =
    useCallback((value, i) => {
      ActionShowProgress |> dispatch;
      i |> upPriceAJax(value);
    });

  let changeItemPrice =
    useCallback((value, i) => ChangeItemPrice(value, i) |> dispatch);

  let showPriceMenu = useCallback(i => ShowPriceMenu(i) |> dispatch);

  let clickPriceMenu =
    useCallback((value, i) => ClickPriceMenu(value, i) |> dispatch);

  let upAllergyAJax = (file, i) => {
    let formData = FormData.make();
    FormData.append(formData, "file", file) |> ignore;
    Js.Promise.(
      formData
      |> Files.upload
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               ShowAllergyFile(response##data##file, i) |> dispatch;
               ActionShowProgress |> dispatch;
             | _ =>
               response##data##status
               |> Status.uploadModels
               |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             }
           )
           |> resolve
         })
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );
  };

  let dragOverAllergy =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowAllergyDrop(true, i) |> dispatch;
    });

  let dragLeaveAllergy =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowAllergyDrop(false, i) |> dispatch;
    });

  let dropItemAllergy =
    useCallback((event, value, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ActionShowProgress |> dispatch;
      ShowAllergyDrop(false, i) |> dispatch;
      i |> upAllergyAJax(value);
    });

  let uploadItemAllergy =
    useCallback((value, i) => {
      ActionShowProgress |> dispatch;
      i |> upAllergyAJax(value);
    });

  let changeItemAllergy =
    useCallback((value, i) => ChangeItemAllergy(value, i) |> dispatch);

  let showAllergyMenu = useCallback(i => ShowAllergyMenu(i) |> dispatch);

  let clickAllergyMenu =
    useCallback((value, i) => ClickAllergyMenu(value, i) |> dispatch);

  let upAlbumAJax = (file, i) => {
    let formData = FormData.make();
    FormData.append(formData, "file", file) |> ignore;
    Js.Promise.(
      formData
      |> Files.upload
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               ShowAlbumFile(response##data##file, i) |> dispatch;
               ActionShowProgress |> dispatch;
             | _ =>
               response##data##status
               |> Status.uploadModels
               |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             }
           )
           |> resolve
         })
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );
  };

  let dragOverAlbum =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowAlbumDrop(true, i) |> dispatch;
    });

  let dragLeaveAlbum =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowAlbumDrop(false, i) |> dispatch;
    });

  let dropItemAlbum =
    useCallback((event, value, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ActionShowProgress |> dispatch;
      ShowAlbumDrop(false, i) |> dispatch;
      i |> upAlbumAJax(value);
    });

  let uploadItemAlbum =
    useCallback((value, i) => {
      ActionShowProgress |> dispatch;
      i |> upAlbumAJax(value);
    });

  let changeItemAlbum =
    useCallback((value, i) => ChangeItemAlbum(value, i) |> dispatch);

  let showAlbumMenu = useCallback(i => ShowAlbumMenu(i) |> dispatch);

  let clickAlbumMenu =
    useCallback((value, i) => ClickAlbumMenu(value, i) |> dispatch);

  let upRemarkAJax = (file, i) => {
    let formData = FormData.make();
    FormData.append(formData, "file", file) |> ignore;
    Js.Promise.(
      formData
      |> Files.upload
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               ShowRemarkFile(response##data##file, i) |> dispatch;
               ActionShowProgress |> dispatch;
             | _ =>
               response##data##status
               |> Status.uploadModels
               |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             }
           )
           |> resolve
         })
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );
  };

  let dragOverRemark =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowRemarkDrop(true, i) |> dispatch;
    });

  let dragLeaveRemark =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowRemarkDrop(false, i) |> dispatch;
    });

  let dropItemRemark =
    useCallback((event, value, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ActionShowProgress |> dispatch;
      ShowRemarkDrop(false, i) |> dispatch;
      i |> upRemarkAJax(value);
    });

  let uploadItemRemark =
    useCallback((value, i) => {
      ActionShowProgress |> dispatch;
      i |> upRemarkAJax(value);
    });

  let changeItemRemark =
    useCallback((value, i) => ChangeItemRemark(value, i) |> dispatch);

  let showRemarkMenu = useCallback(i => ShowRemarkMenu(i) |> dispatch);

  let clickRemarkMenu =
    useCallback((value, i) => ClickRemarkMenu(value, i) |> dispatch);

  let chooseFile =
    useCallback(_
      //Documents.GetElementById.make("uploadFile") |> Action.click)
      =>
        switch (fileRef |> Ref.current |> Js.Nullable.toOption) {
        | None => ()
        | Some(el) => el->ReactDOMRe.domElementToObj##click() |> ignore
        }
      );

  let showMenuForm = useCallback(i => ShowMenuForm(i) |> dispatch);

  let deleteMenuForm = useCallback(i => DeleteMenuForm(i) |> dispatch);

  let addMenuAJax = () =>
    Js.Promise.(
      iItemsData(state.items, "newid" |> Locals.select)
      |> Axiosapi.Carte.addMenu
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               AddMenuForm(response##data##items) |> dispatch;
               ActionShowProgress |> dispatch;
             | _ =>
               response##data##status
               |> Status.statusModule
               |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             }
           )
           |> resolve
         })
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let addMenuItem =
    useCallback(_ => {
      ActionShowProgress |> dispatch;
      addMenuAJax();
    });

  let insertAJax = () =>
    Js.Promise.(
      iFormData(
        state.formId,
        state.tile,
        state.desc,
        Js_array.filter(
          (item: item) =>
            item.itemModify === true
            || item.itemDelete === true
            || item.itemCreate === true,
          state.items,
        ),
        "newid" |> Locals.select,
      )
      |> Axiosapi.Carte.insert
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               RefreshMenuForm |> dispatch;
               "sendSuccess" |> Status.statusModule |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             | _ =>
               response##data##status
               |> Status.statusModule
               |> barShowRestoreAction;
               ActionShowProgress |> dispatch;
             }
           )
           |> resolve
         })
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let insertForm =
    useCallback(_ => {
      ActionShowProgress |> dispatch;
      insertAJax();
    });

  <>
    <NewFacetube showProgress={state.showProgress} error={state.error}>
      <GridItem
        style=marginAuto
        top="0"
        right="0"
        bottom="0"
        left="0"
        xs="12"
        maxWidth="770px">
        <GridContainer direction="column" justify="center" alignItem="stretch">
          <GridItem top="0" right="24" bottom="0" left="24" xs="auto">
            <GridContainer direction="row" justify="center" alignItem="center">
              <GridItem top="0" bottom="0" left="0" xs="auto">
                <TextFieldStandard
                  labelColor="rgba(255,0,0,0.8)"
                  enterBorderColor="rgba(255,0,0,0.8)"
                  downBorderColor="rgba(255,0,0,0.6)"
                  borderColor="rgba(0,0,0,0.2)"
                  placeholder="Project Tile"
                  value={state.tile}
                  disabled={state.showProgress}
                  onChange={event =>
                    ReactEvent.Form.target(event)##value |> changeFormTitle
                  }>
                  <FormattedMessage id="Together.name" defaultMessage="Name" />
                </TextFieldStandard>
              </GridItem>
              <GridItem top="0" right="0" bottom="0" left="0" xs="no">
                <Switch
                  checked={state.checked}
                  circleColor={state.checked |> circle}
                  linearColor={state.checked |> linear}
                  fontColor={state.checked |> font}
                  disabled={state.showProgress}
                  onClick=showChecked>
                  <Typography
                    variant="subtitle1"
                    color="rgba(255,0,0,1)"
                    fontWeight="bolder">
                    <FormattedMessage id="release" defaultMessage="Release" />
                  </Typography>
                </Switch>
              </GridItem>
            </GridContainer>
          </GridItem>
          <GridItem top="0" right="24" left="24" xs="auto">
            <TextFieldStandard
              labelColor="rgba(255,0,0,0.8)"
              enterBorderColor="rgba(255,0,0,0.8)"
              downBorderColor="rgba(255,0,0,0.6)"
              borderColor="rgba(0,0,0,0.2)"
              placeholder="Project Desc"
              value={state.desc}
              disabled={state.showProgress}
              onChange={event =>
                ReactEvent.Form.target(event)##value |> changeFormDescription
              }>
              <FormattedMessage id="Together.remark" defaultMessage="Remark" />
            </TextFieldStandard>
          </GridItem>
          <GridItem top="0" right="24" bottom="0" left="24" xs="auto">
            <Tabs id="bus-" index={state.index} short=20 height="3">
              {state.tabitems
               |> List.mapi((i, tabtitem) =>
                    <Tab
                      showTab={tabtitem.showTabt}
                      maxWidth="111.6"
                      borderRadius="15"
                      id={"bus-" ++ string_of_int(i)}
                      animationName="none"
                      onClick={_ => tabtitem.tabPath |> clickItemTab(i)}>
                      <IconAction
                        width="28"
                        height="28"
                        animation="leftRight"
                        src={tabtitem.tabImage}
                      />
                    </Tab>
                  )
               |> Array.of_list
               |> array}
            </Tabs>
          </GridItem>
          {switch (Js_array.length(state.items)) {
           | 0 =>
             <GridItem top="0" right="24" bottom="0" left="24" xs="auto">
               <Paper
                 style={ReactDOMRe.Style.combine(
                   cursorPointer,
                   ReactDOMRe.Style.make(
                     ~position="relative",
                     ~maxHeight,
                     ~minHeight=maxHeight,
                     (),
                   ),
                 )}
                 top="0"
                 bottom="0"
                 onClick=addMenuItem>
                 <div
                   style={ReactDOMRe.Style.make(
                     ~position="absolute",
                     ~top="50%",
                     ~right="50%",
                     ~transform="translate(50%, -50%)",
                     (),
                   )}>
                   {state.showItem
                      ? <Typography
                          variant="tile" color="rgba(255,0,0,0.8)" noWrap=true>
                          <FormattedMessage
                            id="Carte.firstMenu"
                            defaultMessage="firstMenu"
                          />
                        </Typography>
                      : <ProgressCircular size="80" />}
                 </div>
               </Paper>
             </GridItem>
           | _ =>
             <>
               <GridItem
                 style={ReactDOMRe.Style.make(
                   ~position="sticky",
                   ~top="0px",
                   ~zIndex="1000",
                   (),
                 )}
                 right="24"
                 bottom="0"
                 left="24"
                 xs="auto">
                 <Button
                   width="100%"
                   enterBackgroundColor="rgba(255,0,0,0.8)"
                   downBackgroundColor="rgba(255,0,0,0.6)"
                   backgroundColor="rgba(255,0,0,0.8)"
                   size="large"
                   disabled={state.showProgress}
                   onClick=addMenuItem>
                   <FormattedMessage id="Carte.menu" defaultMessage="Menu" />
                 </Button>
               </GridItem>
               {state.items
                |> Array.mapi((i, item) =>
                     <GridItem right="24" bottom="0" left="24" xs="auto">
                       <GridContainer
                         direction="column"
                         justify="center"
                         alignItem="stretch">
                         <GridItem right="0" left="0" xs="auto">
                           <GridContainer
                             direction="row"
                             justify="center"
                             alignItem="center">
                             <GridItem
                               top="0" right="0" bottom="0" left="0" xs="auto">
                               {item.showName
                                  ? {
                                    switch (item.nameOutValue) {
                                    | "label" =>
                                      <Typography
                                        variant="subtitle2"
                                        style={ReactDOMRe.Style.make(
                                          ~paddingLeft="6px",
                                          ~paddingRight="6px",
                                          (),
                                        )}
                                        noWrap=true>
                                        {item.nameValue |> string}
                                      </Typography>
                                    | "image" =>
                                      <ImageUpload
                                        webLoad={state.showProgress}
                                        showDrop={item.showNameDrop}
                                        showFile={item.showNameFile}
                                        src={item.nameValue}
                                        fileRef
                                        onDragOver={event =>
                                          i |> dragOverName(event)
                                        }
                                        onDragLeave={event =>
                                          i |> dragLeaveName(event)
                                        }
                                        onDrop={event =>
                                          i
                                          |> dropItemName(
                                               event,
                                               ReactEventRe.Synthetic.nativeEvent(
                                                 event,
                                               )##dataTransfer##files[0],
                                             )
                                        }
                                        disabled={
                                          state.showProgress || item.itemDelete
                                        }
                                        onClick=chooseFile
                                        onChange={event =>
                                          i
                                          |> uploadItemName(
                                               ReactEvent.Form.target(event)##files[0],
                                             )
                                        }
                                      />
                                    | "text" =>
                                      <TextFieldOutline
                                        width="50"
                                        top="0"
                                        bottom="0"
                                        left="0"
                                        labelColor="rgba(255,0,0,0.8)"
                                        borderTop="10"
                                        borderBottom="10"
                                        enterBorderColor="rgba(255,0,0,0.8)"
                                        downBorderColor="rgba(255,0,0,0.6)"
                                        borderColor="rgba(0,0,0,0.2)"
                                        value={item.nameValue}
                                        disabled={
                                          state.showProgress || item.itemDelete
                                        }
                                        onChange={event =>
                                          i
                                          |> changeItemName(
                                               ReactEvent.Form.target(event)##value,
                                             )
                                        }>
                                        {item.nameTitle |> string}
                                      </TextFieldOutline>
                                    | "textline" =>
                                      <TextFieldOutline
                                        top="0"
                                        bottom="0"
                                        left="0"
                                        labelColor="rgba(255,0,0,0.8)"
                                        borderTop="10"
                                        borderBottom="10"
                                        enterBorderColor="rgba(255,0,0,0.8)"
                                        downBorderColor="rgba(255,0,0,0.6)"
                                        borderColor="rgba(0,0,0,0.2)"
                                        value={item.nameValue}
                                        disabled={
                                          state.showProgress || item.itemDelete
                                        }
                                        onChange={event =>
                                          i
                                          |> changeItemName(
                                               ReactEvent.Form.target(event)##value,
                                             )
                                        }>
                                        {item.nameTitle |> string}
                                      </TextFieldOutline>
                                    | "textarea" =>
                                      <TextFieldMultiline
                                        top="0"
                                        bottom="0"
                                        left="0"
                                        labelColor="rgba(255,0,0,0.8)"
                                        borderTop="10"
                                        borderBottom="10"
                                        enterBorderColor="rgba(255,0,0,0.8)"
                                        downBorderColor="rgba(255,0,0,0.6)"
                                        borderColor="rgba(0,0,0,0.2)"
                                        rows=3
                                        value={item.nameValue}
                                        disabled={
                                          state.showProgress || item.itemDelete
                                        }
                                        onChange={event =>
                                          i
                                          |> changeItemName(
                                               ReactEvent.Form.target(event)##value,
                                             )
                                        }>
                                        {item.nameTitle |> string}
                                      </TextFieldMultiline>
                                    | _ =>
                                      <>
                                        <SelectOutline
                                          top="0"
                                          bottom="0"
                                          left="0"
                                          labelColor="rgba(255,0,0,0.8)"
                                          tile={item.nameTitle}
                                          enterBorderColor="rgba(255,0,0,0.8)"
                                          downBorderColor="rgba(255,0,0,0.6)"
                                          borderColor="rgba(0,0,0,0.2)"
                                          value={item.nameValue}
                                          disabled={
                                            state.showProgress
                                            || item.itemDelete
                                          }
                                          onClick={_ => i |> showNameMenu}>
                                          ...(
                                               item.showNameMenu
                                                 ? <SelectMenu
                                                     top="50%"
                                                     transform="translate(0, -50%)"
                                                     maxHeight="280"
                                                     minHeight="0"
                                                     topLeft="12"
                                                     topRight="12"
                                                     bottomRight="12"
                                                     bottomLeft="12"
                                                     paddingRight="8"
                                                     paddingLeft="8">
                                                     {item.nameitems
                                                      |> Array.map(nameitem =>
                                                           <MenuItem
                                                             top="0"
                                                             right="8"
                                                             bottom="0"
                                                             left="8"
                                                             disablePadding={
                                                                    nameitem.
                                                                    optionPadding
                                                                    }
                                                             topLeft="12"
                                                             topRight="12"
                                                             bottomRight="12"
                                                             bottomLeft="12"
                                                             onClick={_ =>
                                                               i
                                                               |> clickNameMenu(
                                                                    nameitem.
                                                                    value,
                                                                  )
                                                             }>
                                                             {nameitem.value
                                                              |> string}
                                                           </MenuItem>
                                                         )
                                                      |> array}
                                                   </SelectMenu>
                                                 : null,
                                               <IconGeneral
                                                 animation={
                                                   item.showNameMenu
                                                   |> topDownRorate
                                                 }
                                                 src=arrowDownBlack
                                               />,
                                             )
                                        </SelectOutline>
                                        <BackgroundBoard
                                          showBackground={item.showNameMenu}
                                          backgroundColor="transparent"
                                          onClick={_ => i |> showNameMenu}
                                        />
                                      </>
                                    };
                                  }
                                  : null}
                             </GridItem>
                             <GridItem
                               top="0" right="0" bottom="0" left="0" xs="no">
                               {item.showPrice
                                  ? {
                                    switch (item.priceOutValue) {
                                    | "label" =>
                                      <Typography
                                        variant="subtitle2"
                                        style={ReactDOMRe.Style.make(
                                          ~paddingLeft="6px",
                                          ~paddingRight="6px",
                                          (),
                                        )}
                                        noWrap=true>
                                        {item.priceValue |> string}
                                      </Typography>
                                    | "image" =>
                                      <ImageUpload
                                        webLoad={state.showProgress}
                                        showDrop={item.showPriceDrop}
                                        showFile={item.showPriceFile}
                                        src={item.priceValue}
                                        fileRef
                                        onDragOver={event =>
                                          i |> dragOverPrice(event)
                                        }
                                        onDragLeave={event =>
                                          i |> dragLeavePrice(event)
                                        }
                                        onDrop={event =>
                                          i
                                          |> dropItemPrice(
                                               event,
                                               ReactEventRe.Synthetic.nativeEvent(
                                                 event,
                                               )##dataTransfer##files[0],
                                             )
                                        }
                                        disabled={
                                          state.showProgress || item.itemDelete
                                        }
                                        onClick=chooseFile
                                        onChange={event =>
                                          i
                                          |> uploadItemPrice(
                                               ReactEvent.Form.target(event)##files[0],
                                             )
                                        }
                                      />
                                    | "text" =>
                                      <TextFieldOutline
                                        width="50"
                                        top="0"
                                        bottom="0"
                                        left="0"
                                        labelColor="rgba(255,0,0,0.8)"
                                        borderTop="10"
                                        borderBottom="10"
                                        enterBorderColor="rgba(255,0,0,0.8)"
                                        downBorderColor="rgba(255,0,0,0.6)"
                                        borderColor="rgba(0,0,0,0.2)"
                                        value={item.priceValue}
                                        disabled={
                                          state.showProgress || item.itemDelete
                                        }
                                        onChange={event =>
                                          i
                                          |> changeItemPrice(
                                               ReactEvent.Form.target(event)##value,
                                             )
                                        }>
                                        {item.priceTitle |> string}
                                      </TextFieldOutline>
                                    | "textline" =>
                                      <TextFieldOutline
                                        top="0"
                                        bottom="0"
                                        left="0"
                                        labelColor="rgba(255,0,0,0.8)"
                                        borderTop="10"
                                        borderBottom="10"
                                        enterBorderColor="rgba(255,0,0,0.8)"
                                        downBorderColor="rgba(255,0,0,0.6)"
                                        borderColor="rgba(0,0,0,0.2)"
                                        value={item.priceValue}
                                        disabled={
                                          state.showProgress || item.itemDelete
                                        }
                                        onChange={event =>
                                          i
                                          |> changeItemPrice(
                                               ReactEvent.Form.target(event)##value,
                                             )
                                        }>
                                        {item.priceTitle |> string}
                                      </TextFieldOutline>
                                    | "textarea" =>
                                      <TextFieldMultiline
                                        top="0"
                                        bottom="0"
                                        left="0"
                                        labelColor="rgba(255,0,0,0.8)"
                                        borderTop="10"
                                        borderBottom="10"
                                        enterBorderColor="rgba(255,0,0,0.8)"
                                        downBorderColor="rgba(255,0,0,0.6)"
                                        borderColor="rgba(0,0,0,0.2)"
                                        rows=3
                                        value={item.priceValue}
                                        disabled={
                                          state.showProgress || item.itemDelete
                                        }
                                        onChange={event =>
                                          i
                                          |> changeItemPrice(
                                               ReactEvent.Form.target(event)##value,
                                             )
                                        }>
                                        {item.priceTitle |> string}
                                      </TextFieldMultiline>
                                    | _ =>
                                      <>
                                        <SelectOutline
                                          top="0"
                                          bottom="0"
                                          left="0"
                                          labelColor="rgba(255,0,0,0.8)"
                                          tile={item.priceTitle}
                                          enterBorderColor="rgba(255,0,0,0.8)"
                                          downBorderColor="rgba(255,0,0,0.6)"
                                          borderColor="rgba(0,0,0,0.2)"
                                          value={item.priceValue}
                                          disabled={
                                            state.showProgress
                                            || item.itemDelete
                                          }
                                          onClick={_ => i |> showPriceMenu}>
                                          ...(
                                               item.showPriceMenu
                                                 ? <SelectMenu
                                                     top="50%"
                                                     transform="translate(0, -50%)"
                                                     maxHeight="280"
                                                     minHeight="0"
                                                     topLeft="12"
                                                     topRight="12"
                                                     bottomRight="12"
                                                     bottomLeft="12"
                                                     paddingRight="8"
                                                     paddingLeft="8">
                                                     {item.priceitems
                                                      |> Array.map(priceitem =>
                                                           <MenuItem
                                                             top="0"
                                                             right="8"
                                                             bottom="0"
                                                             left="8"
                                                             disablePadding={
                                                                    priceitem.
                                                                    optionPadding
                                                                    }
                                                             topLeft="12"
                                                             topRight="12"
                                                             bottomRight="12"
                                                             bottomLeft="12"
                                                             onClick={_ =>
                                                               i
                                                               |> clickPriceMenu(
                                                                    priceitem.
                                                                    value,
                                                                  )
                                                             }>
                                                             {priceitem.value
                                                              |> string}
                                                           </MenuItem>
                                                         )
                                                      |> array}
                                                   </SelectMenu>
                                                 : null,
                                               <IconGeneral
                                                 animation={
                                                   item.showPriceMenu
                                                   |> topDownRorate
                                                 }
                                                 src=arrowDownBlack
                                               />,
                                             )
                                        </SelectOutline>
                                        <BackgroundBoard
                                          showBackground={item.showPriceMenu}
                                          backgroundColor="transparent"
                                          onClick={_ => i |> showPriceMenu}
                                        />
                                      </>
                                    };
                                  }
                                  : null}
                             </GridItem>
                             <GridItem
                               style={ReactDOMRe.Style.make(
                                 ~position="relative",
                                 (),
                               )}
                               top="0"
                               right="0"
                               bottom="0"
                               left="0"
                               borderWidth="0"
                               enterBorderWidth="0"
                               xs="no">
                               <IconButton
                                 padding="6" onClick={_ => i |> showMenuForm}>
                                 <Tooltip
                                   location="bottom"
                                   backgroundColor="rgba(255,0,0,0.8)">
                                   <FormattedMessage
                                     id="more"
                                     defaultMessage="More"
                                   />
                                 </Tooltip>
                                 <IconAction
                                   animation="leftRight"
                                   src=moreVertBlack
                                 />
                               </IconButton>
                               {item.showMore
                                  ? <>
                                      <SelectMenu
                                        right="0"
                                        transform="translate(0, -25%)"
                                        maxWidth="344"
                                        width="344"
                                        topLeft="12"
                                        topRight="12"
                                        bottomRight="12"
                                        bottomLeft="12"
                                        paddingRight="8"
                                        paddingLeft="8">
                                        <MenuItem
                                          top="0"
                                          right="8"
                                          bottom="0"
                                          left="8"
                                          topLeft="12"
                                          topRight="12"
                                          bottomRight="12"
                                          bottomLeft="12">
                                          <GridContainer
                                            backgroundColor="transparent"
                                            direction="row"
                                            justify="start"
                                            alignItem="center">
                                            <GridItem
                                              style={ReactDOMRe.Style.make(
                                                ~height="28px",
                                                (),
                                              )}
                                              top="0"
                                              bottom="0"
                                              left="0"
                                              enterBackgroundColor="transparent"
                                              backgroundColor="transparent"
                                              xs="no">
                                              <IconAction
                                                width="28"
                                                height="28"
                                                animation="leftRight"
                                                src=fileCopyBlack
                                              />
                                            </GridItem>
                                            <GridItem
                                              top="0"
                                              right="0"
                                              bottom="0"
                                              left="0"
                                              enterBackgroundColor="transparent"
                                              backgroundColor="transparent"
                                              xs="no">
                                              <Typography variant="subheading">
                                                <FormattedMessage
                                                  id="copy"
                                                  defaultMessage="Copy"
                                                />
                                              </Typography>
                                            </GridItem>
                                          </GridContainer>
                                        </MenuItem>
                                        <MenuItem
                                          top="0"
                                          right="8"
                                          bottom="0"
                                          left="8"
                                          topLeft="12"
                                          topRight="12"
                                          bottomRight="12"
                                          bottomLeft="12"
                                          onClick={_ => i |> deleteMenuForm}>
                                          <GridContainer
                                            backgroundColor="transparent"
                                            direction="row"
                                            justify="start"
                                            alignItem="center">
                                            <GridItem
                                              style={ReactDOMRe.Style.make(
                                                ~height="28px",
                                                (),
                                              )}
                                              top="0"
                                              bottom="0"
                                              left="0"
                                              enterBackgroundColor="transparent"
                                              backgroundColor="transparent"
                                              xs="no">
                                              <IconAction
                                                width="28"
                                                height="28"
                                                animation="leftRight"
                                                src={
                                                  item.itemDelete
                                                    ? refreshBlack : clearWarn
                                                }
                                              />
                                            </GridItem>
                                            <GridItem
                                              top="0"
                                              right="0"
                                              bottom="0"
                                              left="0"
                                              enterBackgroundColor="transparent"
                                              backgroundColor="transparent"
                                              xs="no">
                                              <Typography variant="subheading">
                                                {item.itemDelete
                                                   ? <FormattedMessage
                                                       id="refresh"
                                                       defaultMessage="Refresh"
                                                     />
                                                   : <FormattedMessage
                                                       id="deleted"
                                                       defaultMessage="Deleted"
                                                     />}
                                              </Typography>
                                            </GridItem>
                                          </GridContainer>
                                        </MenuItem>
                                      </SelectMenu>
                                      <BackgroundBoard
                                        showBackground={item.showMore}
                                        backgroundColor="transparent"
                                        onClick={_ => i |> showMenuForm}
                                      />
                                    </>
                                  : null}
                             </GridItem>
                           </GridContainer>
                         </GridItem>
                         <GridItem right="0" left="0" xs="auto">
                           {item.showAllergy
                              ? {
                                switch (item.allergyOutValue) {
                                | "label" =>
                                  <Typography
                                    variant="subtitle2"
                                    style={ReactDOMRe.Style.make(
                                      ~paddingLeft="6px",
                                      ~paddingRight="6px",
                                      (),
                                    )}
                                    noWrap=true>
                                    {item.allergyValue |> string}
                                  </Typography>
                                | "image" =>
                                  <ImageUpload
                                    webLoad={state.showProgress}
                                    showDrop={item.showAllergyDrop}
                                    showFile={item.showAllergyFile}
                                    src={item.allergyValue}
                                    fileRef
                                    onDragOver={event =>
                                      i |> dragOverAllergy(event)
                                    }
                                    onDragLeave={event =>
                                      i |> dragLeaveAllergy(event)
                                    }
                                    onDrop={event =>
                                      i
                                      |> dropItemAllergy(
                                           event,
                                           ReactEventRe.Synthetic.nativeEvent(
                                             event,
                                           )##dataTransfer##files[0],
                                         )
                                    }
                                    disabled={
                                      state.showProgress || item.itemDelete
                                    }
                                    onClick=chooseFile
                                    onChange={event =>
                                      i
                                      |> uploadItemAllergy(
                                           ReactEvent.Form.target(event)##files[0],
                                         )
                                    }
                                  />
                                | "text" =>
                                  <TextFieldOutline
                                    width="50"
                                    top="0"
                                    bottom="0"
                                    left="0"
                                    labelColor="rgba(255,0,0,0.8)"
                                    borderTop="10"
                                    borderBottom="10"
                                    enterBorderColor="rgba(255,0,0,0.8)"
                                    downBorderColor="rgba(255,0,0,0.6)"
                                    borderColor="rgba(0,0,0,0.2)"
                                    value={item.allergyValue}
                                    disabled={
                                      state.showProgress || item.itemDelete
                                    }
                                    onChange={event =>
                                      i
                                      |> changeItemAllergy(
                                           ReactEvent.Form.target(event)##value,
                                         )
                                    }>
                                    {item.allergyTitle |> string}
                                  </TextFieldOutline>
                                | "textline" =>
                                  <TextFieldOutline
                                    top="0"
                                    bottom="0"
                                    left="0"
                                    labelColor="rgba(255,0,0,0.8)"
                                    borderTop="10"
                                    borderBottom="10"
                                    enterBorderColor="rgba(255,0,0,0.8)"
                                    downBorderColor="rgba(255,0,0,0.6)"
                                    borderColor="rgba(0,0,0,0.2)"
                                    value={item.allergyValue}
                                    disabled={
                                      state.showProgress || item.itemDelete
                                    }
                                    onChange={event =>
                                      i
                                      |> changeItemAllergy(
                                           ReactEvent.Form.target(event)##value,
                                         )
                                    }>
                                    {item.allergyTitle |> string}
                                  </TextFieldOutline>
                                | "textarea" =>
                                  <TextFieldMultiline
                                    top="0"
                                    bottom="0"
                                    left="0"
                                    labelColor="rgba(255,0,0,0.8)"
                                    borderTop="10"
                                    borderBottom="10"
                                    enterBorderColor="rgba(255,0,0,0.8)"
                                    downBorderColor="rgba(255,0,0,0.6)"
                                    borderColor="rgba(0,0,0,0.2)"
                                    rows=3
                                    value={item.allergyValue}
                                    disabled={
                                      state.showProgress || item.itemDelete
                                    }
                                    onChange={event =>
                                      i
                                      |> changeItemAllergy(
                                           ReactEvent.Form.target(event)##value,
                                         )
                                    }>
                                    {item.allergyTitle |> string}
                                  </TextFieldMultiline>
                                | _ =>
                                  <>
                                    <SelectOutline
                                      top="0"
                                      bottom="0"
                                      left="0"
                                      labelColor="rgba(255,0,0,0.8)"
                                      tile={item.allergyTitle}
                                      enterBorderColor="rgba(255,0,0,0.8)"
                                      downBorderColor="rgba(255,0,0,0.6)"
                                      borderColor="rgba(0,0,0,0.2)"
                                      value={item.allergyValue}
                                      disabled={
                                        state.showProgress || item.itemDelete
                                      }
                                      onClick={_ => i |> showAllergyMenu}>
                                      ...(
                                           item.showAllergyMenu
                                             ? <SelectMenu
                                                 top="50%"
                                                 transform="translate(0, -50%)"
                                                 maxHeight="280"
                                                 minHeight="0"
                                                 topLeft="12"
                                                 topRight="12"
                                                 bottomRight="12"
                                                 bottomLeft="12"
                                                 paddingRight="8"
                                                 paddingLeft="8">
                                                 {item.allergyitems
                                                  |> Array.map(allergyitem =>
                                                       <MenuItem
                                                         top="0"
                                                         right="8"
                                                         bottom="0"
                                                         left="8"
                                                         disablePadding={
                                                                    allergyitem.
                                                                    optionPadding
                                                                    }
                                                         topLeft="12"
                                                         topRight="12"
                                                         bottomRight="12"
                                                         bottomLeft="12"
                                                         onClick={_ =>
                                                           i
                                                           |> clickAllergyMenu(
                                                                allergyitem.
                                                                  value,
                                                              )
                                                         }>
                                                         {allergyitem.value
                                                          |> string}
                                                       </MenuItem>
                                                     )
                                                  |> array}
                                               </SelectMenu>
                                             : null,
                                           <IconGeneral
                                             animation={
                                               item.showAllergyMenu
                                               |> topDownRorate
                                             }
                                             src=arrowDownBlack
                                           />,
                                         )
                                    </SelectOutline>
                                    <BackgroundBoard
                                      showBackground={item.showAllergyMenu}
                                      backgroundColor="transparent"
                                      onClick={_ => i |> showAllergyMenu}
                                    />
                                  </>
                                };
                              }
                              : null}
                         </GridItem>
                         <GridItem right="0" left="0" xs="auto">
                           {item.showAlbum
                              ? {
                                switch (item.albumOutValue) {
                                | "label" =>
                                  <Typography
                                    variant="subtitle2"
                                    style={ReactDOMRe.Style.make(
                                      ~paddingLeft="6px",
                                      ~paddingRight="6px",
                                      (),
                                    )}
                                    noWrap=true>
                                    {item.albumValue |> string}
                                  </Typography>
                                | "image" =>
                                  <ImageUpload
                                    webLoad={state.showProgress}
                                    showDrop={item.showAlbumDrop}
                                    showFile={item.showAlbumFile}
                                    src={item.albumValue}
                                    fileRef
                                    onDragOver={event =>
                                      i |> dragOverAlbum(event)
                                    }
                                    onDragLeave={event =>
                                      i |> dragLeaveAlbum(event)
                                    }
                                    onDrop={event =>
                                      i
                                      |> dropItemAlbum(
                                           event,
                                           ReactEventRe.Synthetic.nativeEvent(
                                             event,
                                           )##dataTransfer##files[0],
                                         )
                                    }
                                    disabled={
                                      state.showProgress || item.itemDelete
                                    }
                                    onClick=chooseFile
                                    onChange={event =>
                                      i
                                      |> uploadItemAlbum(
                                           ReactEvent.Form.target(event)##files[0],
                                         )
                                    }
                                  />
                                | "text" =>
                                  <TextFieldOutline
                                    width="50"
                                    top="0"
                                    bottom="0"
                                    left="0"
                                    labelColor="rgba(255,0,0,0.8)"
                                    borderTop="10"
                                    borderBottom="10"
                                    enterBorderColor="rgba(255,0,0,0.8)"
                                    downBorderColor="rgba(255,0,0,0.6)"
                                    borderColor="rgba(0,0,0,0.2)"
                                    value={item.albumValue}
                                    disabled={
                                      state.showProgress || item.itemDelete
                                    }
                                    onChange={event =>
                                      i
                                      |> changeItemAlbum(
                                           ReactEvent.Form.target(event)##value,
                                         )
                                    }>
                                    {item.albumTitle |> string}
                                  </TextFieldOutline>
                                | "textline" =>
                                  <TextFieldOutline
                                    top="0"
                                    bottom="0"
                                    left="0"
                                    labelColor="rgba(255,0,0,0.8)"
                                    borderTop="10"
                                    borderBottom="10"
                                    enterBorderColor="rgba(255,0,0,0.8)"
                                    downBorderColor="rgba(255,0,0,0.6)"
                                    borderColor="rgba(0,0,0,0.2)"
                                    value={item.albumValue}
                                    disabled={
                                      state.showProgress || item.itemDelete
                                    }
                                    onChange={event =>
                                      i
                                      |> changeItemAlbum(
                                           ReactEvent.Form.target(event)##value,
                                         )
                                    }>
                                    {item.albumTitle |> string}
                                  </TextFieldOutline>
                                | "textarea" =>
                                  <TextFieldMultiline
                                    top="0"
                                    bottom="0"
                                    left="0"
                                    labelColor="rgba(255,0,0,0.8)"
                                    borderTop="10"
                                    borderBottom="10"
                                    enterBorderColor="rgba(255,0,0,0.8)"
                                    downBorderColor="rgba(255,0,0,0.6)"
                                    borderColor="rgba(0,0,0,0.2)"
                                    rows=3
                                    value={item.albumValue}
                                    disabled={
                                      state.showProgress || item.itemDelete
                                    }
                                    onChange={event =>
                                      i
                                      |> changeItemAlbum(
                                           ReactEvent.Form.target(event)##value,
                                         )
                                    }>
                                    {item.albumTitle |> string}
                                  </TextFieldMultiline>
                                | _ =>
                                  <>
                                    <SelectOutline
                                      top="0"
                                      bottom="0"
                                      left="0"
                                      labelColor="rgba(255,0,0,0.8)"
                                      tile={item.albumTitle}
                                      enterBorderColor="rgba(255,0,0,0.8)"
                                      downBorderColor="rgba(255,0,0,0.6)"
                                      borderColor="rgba(0,0,0,0.2)"
                                      value={item.albumValue}
                                      disabled={
                                        state.showProgress || item.itemDelete
                                      }
                                      onClick={_ => i |> showAlbumMenu}>
                                      ...(
                                           item.showAlbumMenu
                                             ? <SelectMenu
                                                 top="50%"
                                                 transform="translate(0, -50%)"
                                                 maxHeight="280"
                                                 minHeight="0"
                                                 topLeft="12"
                                                 topRight="12"
                                                 bottomRight="12"
                                                 bottomLeft="12"
                                                 paddingRight="8"
                                                 paddingLeft="8">
                                                 {item.albumitems
                                                  |> Array.map(albumitem =>
                                                       <MenuItem
                                                         top="0"
                                                         right="8"
                                                         bottom="0"
                                                         left="8"
                                                         disablePadding={
                                                                    albumitem.
                                                                    optionPadding
                                                                    }
                                                         topLeft="12"
                                                         topRight="12"
                                                         bottomRight="12"
                                                         bottomLeft="12"
                                                         onClick={_ =>
                                                           i
                                                           |> clickAlbumMenu(
                                                                albumitem.
                                                                  value,
                                                              )
                                                         }>
                                                         {albumitem.value
                                                          |> string}
                                                       </MenuItem>
                                                     )
                                                  |> array}
                                               </SelectMenu>
                                             : null,
                                           <IconGeneral
                                             animation={
                                               item.showAlbumMenu
                                               |> topDownRorate
                                             }
                                             src=arrowDownBlack
                                           />,
                                         )
                                    </SelectOutline>
                                    <BackgroundBoard
                                      showBackground={item.showAlbumMenu}
                                      backgroundColor="transparent"
                                      onClick={_ => i |> showAlbumMenu}
                                    />
                                  </>
                                };
                              }
                              : null}
                         </GridItem>
                         <GridItem right="0" left="0" xs="auto">
                           {item.showRemark
                              ? {
                                switch (item.remarkOutValue) {
                                | "label" =>
                                  <Typography
                                    variant="subtitle2"
                                    style={ReactDOMRe.Style.make(
                                      ~paddingLeft="6px",
                                      ~paddingRight="6px",
                                      (),
                                    )}
                                    noWrap=true>
                                    {item.remarkValue |> string}
                                  </Typography>
                                | "image" =>
                                  <ImageUpload
                                    webLoad={state.showProgress}
                                    showDrop={item.showRemarkDrop}
                                    showFile={item.showRemarkFile}
                                    src={item.remarkValue}
                                    fileRef
                                    onDragOver={event =>
                                      i |> dragOverRemark(event)
                                    }
                                    onDragLeave={event =>
                                      i |> dragLeaveRemark(event)
                                    }
                                    onDrop={event =>
                                      i
                                      |> dropItemRemark(
                                           event,
                                           ReactEventRe.Synthetic.nativeEvent(
                                             event,
                                           )##dataTransfer##files[0],
                                         )
                                    }
                                    disabled={
                                      state.showProgress || item.itemDelete
                                    }
                                    onClick=chooseFile
                                    onChange={event =>
                                      i
                                      |> uploadItemRemark(
                                           ReactEvent.Form.target(event)##files[0],
                                         )
                                    }
                                  />
                                | "text" =>
                                  <TextFieldOutline
                                    width="50"
                                    top="0"
                                    bottom="0"
                                    left="0"
                                    labelColor="rgba(255,0,0,0.8)"
                                    borderTop="10"
                                    borderBottom="10"
                                    enterBorderColor="rgba(255,0,0,0.8)"
                                    downBorderColor="rgba(255,0,0,0.6)"
                                    borderColor="rgba(0,0,0,0.2)"
                                    value={item.remarkValue}
                                    disabled={
                                      state.showProgress || item.itemDelete
                                    }
                                    onChange={event =>
                                      i
                                      |> changeItemRemark(
                                           ReactEvent.Form.target(event)##value,
                                         )
                                    }>
                                    {item.remarkTitle |> string}
                                  </TextFieldOutline>
                                | "textline" =>
                                  <TextFieldOutline
                                    top="0"
                                    bottom="0"
                                    left="0"
                                    labelColor="rgba(255,0,0,0.8)"
                                    borderTop="10"
                                    borderBottom="10"
                                    enterBorderColor="rgba(255,0,0,0.8)"
                                    downBorderColor="rgba(255,0,0,0.6)"
                                    borderColor="rgba(0,0,0,0.2)"
                                    value={item.remarkValue}
                                    disabled={
                                      state.showProgress || item.itemDelete
                                    }
                                    onChange={event =>
                                      i
                                      |> changeItemRemark(
                                           ReactEvent.Form.target(event)##value,
                                         )
                                    }>
                                    {item.remarkTitle |> string}
                                  </TextFieldOutline>
                                | "textarea" =>
                                  <TextFieldMultiline
                                    top="0"
                                    bottom="0"
                                    left="0"
                                    labelColor="rgba(255,0,0,0.8)"
                                    borderTop="10"
                                    borderBottom="10"
                                    enterBorderColor="rgba(255,0,0,0.8)"
                                    downBorderColor="rgba(255,0,0,0.6)"
                                    borderColor="rgba(0,0,0,0.2)"
                                    rows=3
                                    value={item.remarkValue}
                                    disabled={
                                      state.showProgress || item.itemDelete
                                    }
                                    onChange={event =>
                                      i
                                      |> changeItemRemark(
                                           ReactEvent.Form.target(event)##value,
                                         )
                                    }>
                                    {item.remarkTitle |> string}
                                  </TextFieldMultiline>
                                | _ =>
                                  <>
                                    <SelectOutline
                                      top="0"
                                      bottom="0"
                                      left="0"
                                      labelColor="rgba(255,0,0,0.8)"
                                      tile={item.remarkTitle}
                                      enterBorderColor="rgba(255,0,0,0.8)"
                                      downBorderColor="rgba(255,0,0,0.6)"
                                      borderColor="rgba(0,0,0,0.2)"
                                      value={item.remarkValue}
                                      disabled={
                                        state.showProgress || item.itemDelete
                                      }
                                      onClick={_ => i |> showRemarkMenu}>
                                      ...(
                                           item.showRemarkMenu
                                             ? <SelectMenu
                                                 top="50%"
                                                 transform="translate(0, -50%)"
                                                 maxHeight="280"
                                                 minHeight="0"
                                                 topLeft="12"
                                                 topRight="12"
                                                 bottomRight="12"
                                                 bottomLeft="12"
                                                 paddingRight="8"
                                                 paddingLeft="8">
                                                 {item.remarkitems
                                                  |> Array.map(remarkitem =>
                                                       <MenuItem
                                                         top="0"
                                                         right="8"
                                                         bottom="0"
                                                         left="8"
                                                         disablePadding={
                                                                    remarkitem.
                                                                    optionPadding
                                                                    }
                                                         topLeft="12"
                                                         topRight="12"
                                                         bottomRight="12"
                                                         bottomLeft="12"
                                                         onClick={_ =>
                                                           i
                                                           |> clickRemarkMenu(
                                                                remarkitem.
                                                                  value,
                                                              )
                                                         }>
                                                         {remarkitem.value
                                                          |> string}
                                                       </MenuItem>
                                                     )
                                                  |> array}
                                               </SelectMenu>
                                             : null,
                                           <IconGeneral
                                             animation={
                                               item.showRemarkMenu
                                               |> topDownRorate
                                             }
                                             src=arrowDownBlack
                                           />,
                                         )
                                    </SelectOutline>
                                    <BackgroundBoard
                                      showBackground={item.showRemarkMenu}
                                      backgroundColor="transparent"
                                      onClick={_ => i |> showRemarkMenu}
                                    />
                                  </>
                                };
                              }
                              : null}
                         </GridItem>
                       </GridContainer>
                     </GridItem>
                   )
                |> array}
             </>
           }}
          <GridItem right="24" left="24" xs="auto">
            <Button
              width="100%"
              enterBackgroundColor="rgba(255,0,0,0.6)"
              backgroundColor="rgba(255,0,0,0.8)"
              size="large"
              disabled={state.showProgress}
              onClick=insertForm>
              <FormattedMessage id="save" defaultMessage="Save" />
            </Button>
          </GridItem>
        </GridContainer>
      </GridItem>
    </NewFacetube>
    <SnackbarYoutube showYoutube={state.showYoutube} position="bottomLeft">
      ...(<span> {state.youtubeText |> string} </span>, null)
    </SnackbarYoutube>
  </>;
};
