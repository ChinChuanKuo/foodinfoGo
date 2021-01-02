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
  typeId: int,
  showType: bool,
  typeOutValue: string,
  typeChecked: bool,
  showTypeDrop: bool,
  showTypeFile: bool,
  typeTitle: string,
  typeValue: string,
  showTypeMenu: bool,
  typeitems: array(optionitem),
  phoneId: int,
  showPhone: bool,
  phoneOutValue: string,
  phoneChecked: bool,
  showPhoneDrop: bool,
  showPhoneFile: bool,
  phoneTitle: string,
  phoneValue: string,
  showPhoneMenu: bool,
  phoneitems: array(optionitem),
  addressId: int,
  showAddress: bool,
  addressOutValue: string,
  addressChecked: bool,
  showAddressDrop: bool,
  showAddressFile: bool,
  addressTitle: string,
  addressValue: string,
  showAddressMenu: bool,
  addressitems: array(optionitem),
};

type state = {
  formLoad: bool,
  showProgress: bool,
  error: bool,
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
  items: array(item),
  showYoutube: bool,
  youtubeText: string,
};

type action =
  | SettingError
  | SettingFormLoad(string)
  | ActionShowProgress
  | ActionPermissItems(bool, bool, bool, bool)
  | SettingFormItems(string, string, bool, array(item))
  | ChangeFormTitle(string)
  | ChangeFormDescription(string)
  | ShowChecked
  | ClickItemTab(int)
  | ShowTypeDrop(bool, int)
  | ShowTypeFile(string, int)
  | ChangeItemType(string, int)
  | ShowTypeMenu(int)
  | ClickTypeMenu(string, int)
  | ShowPhoneDrop(bool, int)
  | ShowPhoneFile(string, int)
  | ChangeItemPhone(string, int)
  | ShowPhoneMenu(int)
  | ClickPhoneMenu(string, int)
  | ShowAddressDrop(bool, int)
  | ShowAddressFile(string, int)
  | ChangeItemAddress(string, int)
  | ShowAddressMenu(int)
  | ClickAddressMenu(string, int)
  | ActionSnackBar(string, bool);

let reducer = (state, action) =>
  switch (action) {
  | SettingError => {...state, error: !state.error}
  | SettingFormLoad(value) => {
      ...state,
      formId: value,
      formLoad: !state.formLoad,
    }
  | ActionShowProgress => {...state, showProgress: !state.showProgress}
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
  | ShowTypeDrop(droped, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, showTypeDrop: droped} : item,
          state.items,
        ),
    }
  | ShowTypeFile(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, typeValue: value, showTypeFile: !item.showTypeFile}
              : item,
          state.items,
        ),
    }
  | ChangeItemType(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, typeValue: value} : item,
          state.items,
        ),
    }
  | ShowTypeMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showTypeMenu: !item.showTypeMenu} : item,
          state.items,
        ),
    }
  | ClickTypeMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, typeValue: value, showTypeMenu: !item.showTypeMenu}
              : item,
          state.items,
        ),
    }
  | ShowPhoneDrop(droped, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, showPhoneDrop: droped} : item,
          state.items,
        ),
    }
  | ShowPhoneFile(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                phoneValue: value,
                showPhoneFile: !item.showPhoneFile,
              }
              : item,
          state.items,
        ),
    }
  | ChangeItemPhone(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, phoneValue: value} : item,
          state.items,
        ),
    }
  | ShowPhoneMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showPhoneMenu: !item.showPhoneMenu} : item,
          state.items,
        ),
    }
  | ClickPhoneMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                phoneValue: value,
                showPhoneMenu: !item.showPhoneMenu,
              }
              : item,
          state.items,
        ),
    }
  | ShowAddressDrop(droped, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showAddressDrop: droped} : item,
          state.items,
        ),
    }
  | ShowAddressFile(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                addressValue: value,
                showAddressFile: !item.showAddressFile,
              }
              : item,
          state.items,
        ),
    }
  | ChangeItemAddress(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, addressValue: value} : item,
          state.items,
        ),
    }
  | ShowAddressMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, showAddressMenu: !item.showAddressMenu} : item,
          state.items,
        ),
    }
  | ClickAddressMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                addressValue: value,
                showAddressMenu: !item.showAddressMenu,
              }
              : item,
          state.items,
        ),
    }
  | ActionSnackBar(youtubeText, showYoutube) => {
      ...state,
      youtubeText,
      showYoutube,
    }
  };

let initialState = {
  formLoad: false,
  showProgress: true,
  error: false,
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
  index: 0,
  tile: "",
  desc: "",
  checked: false,
  items: [||],
  showYoutube: false,
  youtubeText: "",
};

[@react.component]
let make = _ => {
  let (state, dispatch) = useReducer(reducer, initialState);

  let fileRef = useRef(Js.Nullable.null);

  let barShowRestoreAction = youtubeText => {
    ActionSnackBar(youtubeText, true) |> dispatch;
    Js.Global.setTimeout(() => ActionSnackBar("", false) |> dispatch, 5000)
    |> ignore;
  };

  let searchAJax = formId =>
    Js.Promise.(
      dFormData(formId, "newid" |> Locals.select)
      |> Axiosapi.Store.search
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
      let timeId = permissAJax();
      Some(
        () => {
          testtime;
          timeId;
        },
      );
    }
  );

  useEffect0(() => {
    let watcherId =
      ReasonReactRouter.watchUrl(url => {
        SettingFormLoad(ReasonReactRouter.dangerouslyGetInitialUrl().hash)
        |> dispatch;
        ActionShowProgress |> dispatch;
      });
    Some(() => {ReasonReactRouter.unwatchUrl(watcherId)});
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

  let upTypeAJax = (file, i) => {
    let formData = FormData.make();
    FormData.append(formData, "file", file) |> ignore;
    Js.Promise.(
      formData
      |> Files.upload
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               ShowTypeFile(response##data##file, i) |> dispatch;
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

  let dragOverType =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowTypeDrop(true, i) |> dispatch;
    });

  let dragLeaveType =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowTypeDrop(false, i) |> dispatch;
    });

  let dropItemType =
    useCallback((event, value, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ActionShowProgress |> dispatch;
      ShowTypeDrop(false, i) |> dispatch;
      i |> upTypeAJax(value);
    });

  let uploadItemType =
    useCallback((value, i) => {
      ActionShowProgress |> dispatch;
      i |> upTypeAJax(value);
    });

  let changeItemType =
    useCallback((value, i) => ChangeItemType(value, i) |> dispatch);

  let showTypeMenu = useCallback(i => ShowTypeMenu(i) |> dispatch);

  let clickTypeMenu =
    useCallback((value, i) => ClickTypeMenu(value, i) |> dispatch);

  let upPhoneAJax = (file, i) => {
    let formData = FormData.make();
    FormData.append(formData, "file", file) |> ignore;
    Js.Promise.(
      formData
      |> Files.upload
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               ShowPhoneFile(response##data##file, i) |> dispatch;
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

  let dragOverPhone =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowPhoneDrop(true, i) |> dispatch;
    });

  let dragLeavePhone =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowPhoneDrop(false, i) |> dispatch;
    });

  let dropItemPhone =
    useCallback((event, value, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ActionShowProgress |> dispatch;
      ShowPhoneDrop(false, i) |> dispatch;
      i |> upPhoneAJax(value);
    });

  let uploadItemPhone =
    useCallback((value, i) => {
      ActionShowProgress |> dispatch;
      i |> upPhoneAJax(value);
    });

  let changeItemPhone =
    useCallback((value, i) => ChangeItemPhone(value, i) |> dispatch);

  let showPhoneMenu = useCallback(i => ShowPhoneMenu(i) |> dispatch);

  let clickPhoneMenu =
    useCallback((value, i) => ClickPhoneMenu(value, i) |> dispatch);

  let upAddressAJax = (file, i) => {
    let formData = FormData.make();
    FormData.append(formData, "file", file) |> ignore;
    Js.Promise.(
      formData
      |> Files.upload
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               ShowAddressFile(response##data##file, i) |> dispatch;
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

  let dragOverAddress =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowAddressDrop(true, i) |> dispatch;
    });

  let dragLeaveAddress =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowAddressDrop(false, i) |> dispatch;
    });

  let dropItemAddress =
    useCallback((event, value, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ActionShowProgress |> dispatch;
      ShowAddressDrop(false, i) |> dispatch;
      i |> upAddressAJax(value);
    });

  let uploadItemAddress =
    useCallback((value, i) => {
      ActionShowProgress |> dispatch;
      i |> upAddressAJax(value);
    });

  let changeItemAddress =
    useCallback((value, i) => ChangeItemAddress(value, i) |> dispatch);

  let showAddressMenu = useCallback(i => ShowAddressMenu(i) |> dispatch);

  let clickAddressMenu =
    useCallback((value, i) => ClickAddressMenu(value, i) |> dispatch);

  let chooseFile =
    useCallback(_
      //Documents.GetElementById.make("uploadFile") |> Action.click)
      =>
        switch (fileRef |> Ref.current |> Js.Nullable.toOption) {
        | None => ()
        | Some(el) => el->ReactDOMRe.domElementToObj##click() |> ignore
        }
      );

  let insertAJax = () =>
    Js.Promise.(
      iFormData(
        state.formId,
        state.tile,
        state.desc,
        state.items,
        "newid" |> Locals.select,
      )
      |> Axiosapi.Store.insert
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
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
          {state.items
           |> Array.mapi((i, item) =>
                <>
                  <GridItem top="0" right="24" left="24" xs="auto">
                    {item.showType
                       ? {
                         switch (item.typeOutValue) {
                         | "label" =>
                           <Typography
                             variant="subtitle2"
                             style={ReactDOMRe.Style.make(
                               ~paddingLeft="6px",
                               (),
                             )}
                             noWrap=true>
                             {item.typeValue |> string}
                           </Typography>
                         | "image" =>
                           <ImageUpload
                             webLoad={state.showProgress}
                             showDrop={item.showTypeDrop}
                             showFile={item.showTypeFile}
                             src={item.typeValue}
                             fileRef
                             onDragOver={event => i |> dragOverType(event)}
                             onDragLeave={event => i |> dragLeaveType(event)}
                             onDrop={event =>
                               dropItemType(
                                 event,
                                 ReactEventRe.Synthetic.nativeEvent(event)##dataTransfer##files[0],
                                 i,
                               )
                             }
                             disabled={state.showProgress}
                             onClick=chooseFile
                             onChange={event =>
                               i
                               |> uploadItemType(
                                    ReactEvent.Form.target(event)##files[0],
                                  )
                             }
                           />
                         | "text" =>
                           <TextFieldStandard
                             width="50"
                             labelColor="rgba(255,0,0,0.8)"
                             enterBorderColor="rgba(255,0,0,0.8)"
                             downBorderColor="rgba(255,0,0,0.6)"
                             borderColor="rgba(0,0,0,0.2)"
                             value={item.typeValue}
                             disabled={state.showProgress}
                             onChange={event =>
                               i
                               |> changeItemType(
                                    ReactEvent.Form.target(event)##value,
                                  )
                             }>
                             {item.typeTitle |> string}
                           </TextFieldStandard>
                         | "textarea" =>
                           <TextFieldStandard
                             labelColor="rgba(255,0,0,0.8)"
                             enterBorderColor="rgba(255,0,0,0.8)"
                             downBorderColor="rgba(255,0,0,0.6)"
                             borderColor="rgba(0,0,0,0.2)"
                             value={item.typeValue}
                             disabled={state.showProgress}
                             onChange={event =>
                               i
                               |> changeItemType(
                                    ReactEvent.Form.target(event)##value,
                                  )
                             }>
                             {item.typeTitle |> string}
                           </TextFieldStandard>
                         | "textline" =>
                           <TextFieldMultiline
                             labelColor="rgba(255,0,0,0.8)"
                             enterBorderColor="rgba(255,0,0,0.8)"
                             downBorderColor="rgba(255,0,0,0.6)"
                             borderColor="rgba(0,0,0,0.2)"
                             rows=3
                             value={item.typeValue}
                             disabled={state.showProgress}
                             onChange={event =>
                               i
                               |> changeItemType(
                                    ReactEvent.Form.target(event)##value,
                                  )
                             }>
                             {item.typeTitle |> string}
                           </TextFieldMultiline>
                         | _ =>
                           <>
                             <SelectStandard
                               width="50"
                               labelColor="rgba(255,0,0,0.8)"
                               tile={item.typeTitle}
                               enterBorderColor="rgba(255,0,0,0.8)"
                               downBorderColor="rgba(255,0,0,0.6)"
                               borderColor="rgba(0,0,0,0.2)"
                               value={item.typeValue}
                               disabled={state.showProgress}
                               onClick={_ => i |> showTypeMenu}>
                               ...(
                                    item.showTypeMenu
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
                                          {item.typeitems
                                           |> Array.map(typeitem =>
                                                <MenuItem
                                                  top="0"
                                                  right="8"
                                                  bottom="0"
                                                  left="8"
                                                  disablePadding={
                                                                   typeitem.
                                                                    optionPadding
                                                                 }
                                                  topLeft="12"
                                                  topRight="12"
                                                  bottomRight="12"
                                                  bottomLeft="12"
                                                  onClick={_ =>
                                                    i
                                                    |> clickTypeMenu(
                                                         typeitem.value,
                                                       )
                                                  }>
                                                  {typeitem.value |> string}
                                                </MenuItem>
                                              )
                                           |> array}
                                        </SelectMenu>
                                      : null,
                                    <IconGeneral
                                      animation={
                                        item.showTypeMenu |> topDownRorate
                                      }
                                      src=arrowDownBlack
                                    />,
                                  )
                             </SelectStandard>
                             <BackgroundBoard
                               showBackground={item.showTypeMenu}
                               backgroundColor="transparent"
                               onClick={_ => i |> showTypeMenu}
                             />
                           </>
                         };
                       }
                       : null}
                  </GridItem>
                  <GridItem top="0" right="24" left="24" xs="auto">
                    {item.showPhone
                       ? {
                         switch (item.phoneOutValue) {
                         | "label" =>
                           <Typography
                             variant="subtitle2"
                             style={ReactDOMRe.Style.make(
                               ~paddingLeft="6px",
                               (),
                             )}
                             noWrap=true>
                             {item.phoneValue |> string}
                           </Typography>
                         | "image" =>
                           <ImageUpload
                             webLoad={state.showProgress}
                             showDrop={item.showPhoneDrop}
                             showFile={item.showPhoneFile}
                             src={item.phoneValue}
                             fileRef
                             onDragOver={event => i |> dragOverPhone(event)}
                             onDragLeave={event => i |> dragLeavePhone(event)}
                             onDrop={event =>
                               i
                               |> dropItemPhone(
                                    event,
                                    ReactEventRe.Synthetic.nativeEvent(event)##dataTransfer##files[0],
                                  )
                             }
                             disabled={state.showProgress}
                             onClick=chooseFile
                             onChange={event =>
                               i
                               |> uploadItemPhone(
                                    ReactEvent.Form.target(event)##files[0],
                                  )
                             }
                           />
                         | "text" =>
                           <TextFieldStandard
                             width="50"
                             labelColor="rgba(255,0,0,0.8)"
                             enterBorderColor="rgba(255,0,0,0.8)"
                             downBorderColor="rgba(255,0,0,0.6)"
                             borderColor="rgba(0,0,0,0.2)"
                             value={item.phoneValue}
                             disabled={state.showProgress}
                             onChange={event =>
                               i
                               |> changeItemPhone(
                                    ReactEvent.Form.target(event)##value,
                                  )
                             }>
                             {item.phoneTitle |> string}
                           </TextFieldStandard>
                         | "textarea" =>
                           <TextFieldStandard
                             labelColor="rgba(255,0,0,0.8)"
                             enterBorderColor="rgba(255,0,0,0.8)"
                             downBorderColor="rgba(255,0,0,0.6)"
                             borderColor="rgba(0,0,0,0.2)"
                             value={item.phoneValue}
                             disabled={state.showProgress}
                             onChange={event =>
                               i
                               |> changeItemPhone(
                                    ReactEvent.Form.target(event)##value,
                                  )
                             }>
                             {item.phoneTitle |> string}
                           </TextFieldStandard>
                         | "textline" =>
                           <TextFieldMultiline
                             labelColor="rgba(255,0,0,0.8)"
                             enterBorderColor="rgba(255,0,0,0.8)"
                             downBorderColor="rgba(255,0,0,0.6)"
                             borderColor="rgba(0,0,0,0.2)"
                             rows=3
                             value={item.phoneValue}
                             disabled={state.showProgress}
                             onChange={event =>
                               i
                               |> changeItemPhone(
                                    ReactEvent.Form.target(event)##value,
                                  )
                             }>
                             {item.phoneTitle |> string}
                           </TextFieldMultiline>
                         | _ =>
                           <>
                             <SelectStandard
                               labelColor="rgba(255,0,0,0.8)"
                               tile={item.phoneTitle}
                               enterBorderColor="rgba(255,0,0,0.8)"
                               downBorderColor="rgba(255,0,0,0.6)"
                               borderColor="rgba(0,0,0,0.2)"
                               value={item.phoneValue}
                               disabled={state.showProgress}
                               onClick={_ => i |> showPhoneMenu}>
                               ...(
                                    item.showPhoneMenu
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
                                          {item.phoneitems
                                           |> Array.map(phoneitem =>
                                                <MenuItem
                                                  top="0"
                                                  right="8"
                                                  bottom="0"
                                                  left="8"
                                                  disablePadding={
                                                                   phoneitem.
                                                                    optionPadding
                                                                 }
                                                  topLeft="12"
                                                  topRight="12"
                                                  bottomRight="12"
                                                  bottomLeft="12"
                                                  onClick={_ =>
                                                    i
                                                    |> clickPhoneMenu(
                                                         phoneitem.value,
                                                       )
                                                  }>
                                                  {phoneitem.value |> string}
                                                </MenuItem>
                                              )
                                           |> array}
                                        </SelectMenu>
                                      : null,
                                    <IconGeneral
                                      animation={
                                        item.showPhoneMenu |> topDownRorate
                                      }
                                      src=arrowDownBlack
                                    />,
                                  )
                             </SelectStandard>
                             <BackgroundBoard
                               showBackground={item.showPhoneMenu}
                               backgroundColor="transparent"
                               onClick={_ => i |> showPhoneMenu}
                             />
                           </>
                         };
                       }
                       : null}
                  </GridItem>
                  <GridItem top="0" right="24" left="24" xs="auto">
                    {item.showAddress
                       ? {
                         switch (item.addressOutValue) {
                         | "label" =>
                           <Typography
                             variant="subtitle2"
                             style={ReactDOMRe.Style.make(
                               ~paddingLeft="6px",
                               (),
                             )}
                             noWrap=true>
                             {item.addressValue |> string}
                           </Typography>
                         | "image" =>
                           <ImageUpload
                             webLoad={state.showProgress}
                             showDrop={item.showAddressDrop}
                             showFile={item.showAddressFile}
                             src={item.addressValue}
                             fileRef
                             onDragOver={event => i |> dragOverAddress(event)}
                             onDragLeave={event =>
                               i |> dragLeaveAddress(event)
                             }
                             onDrop={event =>
                               i
                               |> dropItemAddress(
                                    event,
                                    ReactEventRe.Synthetic.nativeEvent(event)##dataTransfer##files[0],
                                  )
                             }
                             disabled={state.showProgress}
                             onClick=chooseFile
                             onChange={event =>
                               i
                               |> uploadItemAddress(
                                    ReactEvent.Form.target(event)##files[0],
                                  )
                             }
                           />
                         | "text" =>
                           <TextFieldStandard
                             width="50"
                             labelColor="rgba(255,0,0,0.8)"
                             enterBorderColor="rgba(255,0,0,0.8)"
                             downBorderColor="rgba(255,0,0,0.6)"
                             borderColor="rgba(0,0,0,0.2)"
                             value={item.addressValue}
                             disabled={state.showProgress}
                             onChange={event =>
                               i
                               |> changeItemAddress(
                                    ReactEvent.Form.target(event)##value,
                                  )
                             }>
                             {item.addressTitle |> string}
                           </TextFieldStandard>
                         | "textarea" =>
                           <TextFieldStandard
                             labelColor="rgba(255,0,0,0.8)"
                             enterBorderColor="rgba(255,0,0,0.8)"
                             downBorderColor="rgba(255,0,0,0.6)"
                             borderColor="rgba(0,0,0,0.2)"
                             value={item.addressValue}
                             disabled={state.showProgress}
                             onChange={event =>
                               i
                               |> changeItemAddress(
                                    ReactEvent.Form.target(event)##value,
                                  )
                             }>
                             {item.addressTitle |> string}
                           </TextFieldStandard>
                         | "textline" =>
                           <TextFieldMultiline
                             labelColor="rgba(255,0,0,0.8)"
                             enterBorderColor="rgba(255,0,0,0.8)"
                             downBorderColor="rgba(255,0,0,0.6)"
                             borderColor="rgba(0,0,0,0.2)"
                             rows=3
                             value={item.addressValue}
                             disabled={state.showProgress}
                             onChange={event =>
                               i
                               |> changeItemAddress(
                                    ReactEvent.Form.target(event)##value,
                                  )
                             }>
                             {item.addressTitle |> string}
                           </TextFieldMultiline>
                         | _ =>
                           <>
                             <SelectStandard
                               labelColor="rgba(255,0,0,0.8)"
                               tile={item.addressTitle}
                               enterBorderColor="rgba(255,0,0,0.8)"
                               downBorderColor="rgba(255,0,0,0.6)"
                               borderColor="rgba(0,0,0,0.2)"
                               value={item.addressValue}
                               disabled={state.showProgress}
                               onClick={_ => i |> showAddressMenu}>
                               ...(
                                    item.showAddressMenu
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
                                          {item.addressitems
                                           |> Array.map(addressitem =>
                                                <MenuItem
                                                  top="0"
                                                  right="8"
                                                  bottom="0"
                                                  left="8"
                                                  disablePadding={
                                                                   addressitem.
                                                                    optionPadding
                                                                 }
                                                  topLeft="12"
                                                  topRight="12"
                                                  bottomRight="12"
                                                  bottomLeft="12"
                                                  onClick={_ =>
                                                    i
                                                    |> clickAddressMenu(
                                                         addressitem.value,
                                                       )
                                                  }>
                                                  {addressitem.value |> string}
                                                </MenuItem>
                                              )
                                           |> array}
                                        </SelectMenu>
                                      : null,
                                    <IconGeneral
                                      animation={
                                        item.showAddressMenu |> topDownRorate
                                      }
                                      src=arrowDownBlack
                                    />,
                                  )
                             </SelectStandard>
                             <BackgroundBoard
                               showBackground={item.showAddressMenu}
                               backgroundColor="transparent"
                               onClick={_ => i |> showAddressMenu}
                             />
                           </>
                         };
                       }
                       : null}
                  </GridItem>
                </>
              )
           |> array}
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
