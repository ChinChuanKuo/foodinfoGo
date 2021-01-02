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
  daId: int,
  festId: string,
  showFest: bool,
  festOutValue: string,
  festChecked: bool,
  showFestDrop: bool,
  showFestFile: bool,
  festValue: string,
  showFestMenu: bool,
  festitems: array(optionitem),
  dateId: string,
  showDate: bool,
  dateOutValue: string,
  dateChecked: bool,
  showDateDrop: bool,
  showDateFile: bool,
  dateValue: string,
  showDateMenu: bool,
  dateitems: array(optionitem),
  sttimeId: string,
  showSttime: bool,
  sttimeOutValue: string,
  sttimeChecked: bool,
  showSttimeDrop: bool,
  showSttimeFile: bool,
  sttimeValue: string,
  showSttimeMenu: bool,
  sttimeitems: array(optionitem),
  entimeId: string,
  showEntime: bool,
  entimeOutValue: string,
  entimeChecked: bool,
  showEntimeDrop: bool,
  showEntimeFile: bool,
  entimeValue: string,
  showEntimeMenu: bool,
  entimeitems: array(optionitem),
  showEnter: bool,
  showModify: bool,
};

type state = {
  formLoad: bool,
  formWidth: int,
  formHeight: int,
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
  heads: array(string),
  items: array(item),
  showYoutube: bool,
  youtubeText: string,
};

type action =
  | SettingError
  | SettingFormLoad(string)
  | SettingFormWidth(int, int)
  | ActionShowProgress
  | ActionPermissItems(bool, bool, bool, bool)
  | SettingFormItems(string, string, bool, array(string), array(item))
  | ChangeFormTitle(string)
  | ChangeFormDescription(string)
  | ShowChecked
  | ClickItemTab(int)
  | ShowFestDrop(bool, int)
  | ShowFestFile(string, int)
  | ChangeItemFest(string, int)
  | ShowFestMenu(int)
  | ClickFestMenu(string, int)
  | ShowDateDrop(bool, int)
  | ShowDateFile(string, int)
  | ChangeItemDate(string, int)
  | ShowDateMenu(int)
  | ClickDateMenu(string, int)
  | ShowSttimeDrop(bool, int)
  | ShowSttimeFile(string, int)
  | ChangeItemSttime(string, int)
  | ShowSttimeMenu(int)
  | ClickSttimeMenu(string, int)
  | ShowEntimeDrop(bool, int)
  | ShowEntimeFile(string, int)
  | ChangeItemEntime(string, int)
  | ShowEntimeMenu(int)
  | ClickEntimeMenu(string, int)
  | MouseEnterLeave(bool, int)
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
  | ActionPermissItems(insert, update, delete, export) => {
      ...state,
      insert,
      update,
      delete,
      export,
    }
  | SettingFormItems(tile, desc, checked, heads, items) => {
      ...state,
      tile,
      desc,
      checked,
      heads,
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
  | ShowFestDrop(droped, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, showFestDrop: droped} : item,
          state.items,
        ),
    }
  | ShowFestFile(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                festValue: value,
                showFestFile: !item.showFestFile,
                showModify: true,
              }
              : item,
          state.items,
        ),
    }
  | ChangeItemFest(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, festValue: value, showModify: true} : item,
          state.items,
        ),
    }
  | ShowFestMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showFestMenu: !item.showFestMenu} : item,
          state.items,
        ),
    }
  | ClickFestMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                festValue: value,
                showFestMenu: !item.showFestMenu,
                showModify: true,
              }
              : item,
          state.items,
        ),
    }
  | ShowDateDrop(droped, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, showDateDrop: droped} : item,
          state.items,
        ),
    }
  | ShowDateFile(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                dateValue: value,
                showDateFile: !item.showDateFile,
                showModify: true,
              }
              : item,
          state.items,
        ),
    }
  | ChangeItemDate(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, dateValue: value, showModify: true} : item,
          state.items,
        ),
    }
  | ShowDateMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showDateMenu: !item.showDateMenu} : item,
          state.items,
        ),
    }
  | ClickDateMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                dateValue: value,
                showDateMenu: !item.showDateMenu,
                showModify: true,
              }
              : item,
          state.items,
        ),
    }
  | ShowSttimeDrop(droped, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, showSttimeDrop: droped} : item,
          state.items,
        ),
    }
  | ShowSttimeFile(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                sttimeValue: value,
                showSttimeFile: !item.showSttimeFile,
                showModify: true,
              }
              : item,
          state.items,
        ),
    }
  | ChangeItemSttime(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, sttimeValue: value, showModify: true} : item,
          state.items,
        ),
    }
  | ShowSttimeMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, showSttimeMenu: !item.showSttimeMenu} : item,
          state.items,
        ),
    }
  | ClickSttimeMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                sttimeValue: value,
                showSttimeMenu: !item.showSttimeMenu,
                showModify: true,
              }
              : item,
          state.items,
        ),
    }
  | ShowEntimeDrop(droped, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, showEntimeDrop: droped} : item,
          state.items,
        ),
    }
  | ShowEntimeFile(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                entimeValue: value,
                showEntimeFile: !item.showEntimeFile,
                showModify: true,
              }
              : item,
          state.items,
        ),
    }
  | ChangeItemEntime(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, entimeValue: value, showModify: true} : item,
          state.items,
        ),
    }
  | ShowEntimeMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {...item, showEntimeMenu: !item.showEntimeMenu} : item,
          state.items,
        ),
    }
  | ClickEntimeMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                entimeValue: value,
                showEntimeMenu: !item.showEntimeMenu,
                showModify: true,
              }
              : item,
          state.items,
        ),
    }
  | MouseEnterLeave(showEnter, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, showEnter} : item,
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
  formWidth: 0,
  formHeight: 0,
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
  index: 3,
  tile: "",
  desc: "",
  checked: false,
  heads: [||],
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
      |> Axiosapi.Fesdate.search
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               SettingFormItems(
                 response##data##tile,
                 response##data##desc,
                 response##data##checked,
                 response##data##heads,
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

  let upFestAJax = (file, i) => {
    let formData = FormData.make();
    FormData.append(formData, "file", file) |> ignore;
    Js.Promise.(
      formData
      |> Files.upload
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               ShowFestFile(response##data##file, i) |> dispatch;
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

  let dragOverFest =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowFestDrop(true, i) |> dispatch;
    });

  let dragLeaveFest =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowFestDrop(false, i) |> dispatch;
    });

  let dropItemFest =
    useCallback((event, value, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ActionShowProgress |> dispatch;
      ShowFestDrop(false, i) |> dispatch;
      i |> upFestAJax(value);
    });

  let uploadItemFest =
    useCallback((value, i) => {
      ActionShowProgress |> dispatch;
      i |> upFestAJax(value);
    });

  let changeItemFest =
    useCallback((value, i) => ChangeItemFest(value, i) |> dispatch);

  let showFestMenu = useCallback(i => ShowFestMenu(i) |> dispatch);

  let clickFestMenu =
    useCallback((value, i) => ClickFestMenu(value, i) |> dispatch);

  let upDateAJax = (file, i) => {
    let formData = FormData.make();
    FormData.append(formData, "file", file) |> ignore;
    Js.Promise.(
      formData
      |> Files.upload
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               ShowDateFile(response##data##file, i) |> dispatch;
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

  let dragOverDate =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowDateDrop(true, i) |> dispatch;
    });

  let dragLeaveDate =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowDateDrop(false, i) |> dispatch;
    });

  let dropItemDate =
    useCallback((event, value, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ActionShowProgress |> dispatch;
      ShowDateDrop(false, i) |> dispatch;
      i |> upDateAJax(value);
    });

  let uploadItemDate =
    useCallback((value, i) => {
      ActionShowProgress |> dispatch;
      i |> upDateAJax(value);
    });

  let changeItemDate =
    useCallback((value, i) => ChangeItemDate(value, i) |> dispatch);

  let showDateMenu = useCallback(i => ShowDateMenu(i) |> dispatch);

  let clickDateMenu =
    useCallback((value, i) => ClickDateMenu(value, i) |> dispatch);

  let upSttimeAJax = (file, i) => {
    let formData = FormData.make();
    FormData.append(formData, "file", file) |> ignore;
    Js.Promise.(
      formData
      |> Files.upload
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               ShowSttimeFile(response##data##file, i) |> dispatch;
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

  let dragOverSttime =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowSttimeDrop(true, i) |> dispatch;
    });

  let dragLeaveSttime =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowSttimeDrop(false, i) |> dispatch;
    });

  let dropItemSttime =
    useCallback((event, value, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ActionShowProgress |> dispatch;
      ShowSttimeDrop(false, i) |> dispatch;
      i |> upSttimeAJax(value);
    });

  let uploadItemSttime =
    useCallback((value, i) => {
      ActionShowProgress |> dispatch;
      i |> upSttimeAJax(value);
    });

  let changeItemSttime =
    useCallback((value, i) => ChangeItemSttime(value, i) |> dispatch);

  let showSttimeMenu = useCallback(i => ShowSttimeMenu(i) |> dispatch);

  let clickSttimeMenu =
    useCallback((value, i) => ClickSttimeMenu(value, i) |> dispatch);

  let upEntimeAJax = (file, i) => {
    let formData = FormData.make();
    FormData.append(formData, "file", file) |> ignore;
    Js.Promise.(
      formData
      |> Files.upload
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               ShowEntimeFile(response##data##file, i) |> dispatch;
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

  let dragOverEntime =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowEntimeDrop(true, i) |> dispatch;
    });

  let dragLeaveEntime =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowEntimeDrop(false, i) |> dispatch;
    });

  let dropItemEntime =
    useCallback((event, value, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ActionShowProgress |> dispatch;
      ShowEntimeDrop(false, i) |> dispatch;
      i |> upEntimeAJax(value);
    });

  let uploadItemEntime =
    useCallback((value, i) => {
      ActionShowProgress |> dispatch;
      i |> upEntimeAJax(value);
    });

  let changeItemEntime =
    useCallback((value, i) => ChangeItemEntime(value, i) |> dispatch);

  let showEntimeMenu = useCallback(i => ShowEntimeMenu(i) |> dispatch);

  let clickEntimeMenu =
    useCallback((value, i) => ClickEntimeMenu(value, i) |> dispatch);

  let mouseEnterLeave =
    useCallback((enter, i) => MouseEnterLeave(enter, i) |> dispatch);

  let dragStart =
    useCallback(event =>
      ReactEventRe.Synthetic.nativeEvent(event)##currentTarget |> Js.log
    );

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
        Js_array.filter(
          (item: item) => item.showModify === true,
          state.items,
        ),
        "newid" |> Locals.select,
      )
      |> Axiosapi.Fesdate.insert
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
            <GridContainer direction="row" justify="center" alignItem="center">
              {state.heads
               |> Array.map(head =>
                    <GridItem right="6" bottom="0" left="6" xs="auto">
                      {head |> string}
                    </GridItem>
                  )
               |> array}
              <GridItem
                style={ReactDOMRe.Style.make(~height="8px", ())}
                width="8px"
                xs="no">
                null
              </GridItem>
            </GridContainer>
          </GridItem>
          <GridItem top="0" right="24" left="24" xs="auto">
            <GridContainer
              direction="column" justify="center" alignItem="stretch">
              {state.items
               |> Array.mapi((i, item) =>
                    <GridItem
                      right="0"
                      left="0"
                      xs="auto"
                      onMouseEnter={_ => i |> mouseEnterLeave(true)}
                      onMouseLeave={_ => i |> mouseEnterLeave(false)}>
                      <div onDragStart={event => event |> dragStart}>
                        <GridContainer
                          direction="row" justify="start" alignItem="center">
                          <GridItem
                            top="0" right="0" bottom="0" left="0" xs="auto">
                            {item.showFest
                               ? {
                                 switch (item.festOutValue) {
                                 | "label" =>
                                   <Typography
                                     variant="subtitle2"
                                     style={ReactDOMRe.Style.make(
                                       ~paddingLeft="6px",
                                       ~paddingRight="6px",
                                       (),
                                     )}
                                     noWrap=true>
                                     {item.festValue |> string}
                                   </Typography>
                                 | "image" =>
                                   <ImageUpload
                                     webLoad={state.showProgress}
                                     showDrop={item.showFestDrop}
                                     showFile={item.showFestFile}
                                     src={item.festValue}
                                     fileRef
                                     onDragOver={event =>
                                       i |> dragOverFest(event)
                                     }
                                     onDragLeave={event =>
                                       i |> dragLeaveFest(event)
                                     }
                                     onDrop={event =>
                                       i
                                       |> dropItemFest(
                                            event,
                                            ReactEventRe.Synthetic.nativeEvent(
                                              event,
                                            )##dataTransfer##files[0],
                                          )
                                     }
                                     disabled={state.showProgress}
                                     onClick=chooseFile
                                     onChange={event =>
                                       i
                                       |> uploadItemFest(
                                            ReactEvent.Form.target(event)##files[0],
                                          )
                                     }
                                   />
                                 | "text" =>
                                   <TextFieldOutline
                                     width="50"
                                     top="0"
                                     left="0"
                                     borderTop="10"
                                     borderBottom="10"
                                     enterBorderColor="rgba(255,0,0,0.8)"
                                     downBorderColor="rgba(255,0,0,0.6)"
                                     borderColor="rgba(0,0,0,0.2)"
                                     value={item.festValue}
                                     disabled={state.showProgress}
                                     onChange={event =>
                                       i
                                       |> changeItemFest(
                                            ReactEvent.Form.target(event)##value,
                                          )
                                     }>
                                     null
                                   </TextFieldOutline>
                                 | "textarea" =>
                                   <TextFieldOutline
                                     top="0"
                                     left="0"
                                     borderTop="10"
                                     borderBottom="10"
                                     enterBorderColor="rgba(255,0,0,0.8)"
                                     downBorderColor="rgba(255,0,0,0.6)"
                                     borderColor="rgba(0,0,0,0.2)"
                                     value={item.festValue}
                                     disabled={state.showProgress}
                                     onChange={event =>
                                       i
                                       |> changeItemFest(
                                            ReactEvent.Form.target(event)##value,
                                          )
                                     }>
                                     null
                                   </TextFieldOutline>
                                 | _ =>
                                   <>
                                     <SelectOutline
                                       top="0"
                                       left="0"
                                       enterBorderColor="rgba(255,0,0,0.8)"
                                       downBorderColor="rgba(255,0,0,0.6)"
                                       borderColor="rgba(0,0,0,0.2)"
                                       value={item.festValue}
                                       disabled={state.showProgress}
                                       onClick={_ => i |> showFestMenu}>
                                       ...(
                                            item.showFestMenu
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
                                                  {item.festitems
                                                   |> Array.map(festitem =>
                                                        <MenuItem
                                                          top="0"
                                                          right="8"
                                                          bottom="0"
                                                          left="8"
                                                          disablePadding={
                                                                    festitem.
                                                                    optionPadding
                                                                    }
                                                          topLeft="12"
                                                          topRight="12"
                                                          bottomRight="12"
                                                          bottomLeft="12"
                                                          onClick={_ =>
                                                            i
                                                            |> clickFestMenu(
                                                                 festitem.
                                                                   value,
                                                               )
                                                          }>
                                                          {festitem.value
                                                           |> string}
                                                        </MenuItem>
                                                      )
                                                   |> array}
                                                </SelectMenu>
                                              : null,
                                            <IconGeneral
                                              animation={
                                                item.showFestMenu
                                                |> topDownRorate
                                              }
                                              src=arrowDownBlack
                                            />,
                                          )
                                     </SelectOutline>
                                     <BackgroundBoard
                                       showBackground={item.showFestMenu}
                                       backgroundColor="transparent"
                                       onClick={_ => i |> showFestMenu}
                                     />
                                   </>
                                 };
                               }
                               : null}
                          </GridItem>
                          <GridItem
                            top="0" right="0" bottom="0" left="0" xs="auto">
                            {item.showDate
                               ? {
                                 switch (item.dateOutValue) {
                                 | "label" =>
                                   <Typography
                                     variant="subtitle2"
                                     style={ReactDOMRe.Style.make(
                                       ~paddingLeft="6px",
                                       ~paddingRight="6px",
                                       (),
                                     )}
                                     noWrap=true>
                                     {item.dateValue |> string}
                                   </Typography>
                                 | "image" =>
                                   <ImageUpload
                                     webLoad={state.showProgress}
                                     showDrop={item.showDateDrop}
                                     showFile={item.showDateFile}
                                     src={item.dateValue}
                                     fileRef
                                     onDragOver={event =>
                                       i |> dragOverDate(event)
                                     }
                                     onDragLeave={event =>
                                       i |> dragLeaveDate(event)
                                     }
                                     onDrop={event =>
                                       i
                                       |> dropItemDate(
                                            event,
                                            ReactEventRe.Synthetic.nativeEvent(
                                              event,
                                            )##dataTransfer##files[0],
                                          )
                                     }
                                     disabled={state.showProgress}
                                     onClick=chooseFile
                                     onChange={event =>
                                       i
                                       |> uploadItemDate(
                                            ReactEvent.Form.target(event)##files[0],
                                          )
                                     }
                                   />
                                 | "text" =>
                                   <TextFieldOutline
                                     width="50"
                                     top="0"
                                     left="0"
                                     borderTop="10"
                                     borderBottom="10"
                                     enterBorderColor="rgba(255,0,0,0.8)"
                                     downBorderColor="rgba(255,0,0,0.6)"
                                     borderColor="rgba(0,0,0,0.2)"
                                     value={item.dateValue}
                                     disabled={state.showProgress}
                                     onChange={event =>
                                       i
                                       |> changeItemDate(
                                            ReactEvent.Form.target(event)##value,
                                          )
                                     }>
                                     null
                                   </TextFieldOutline>
                                 | "textarea" =>
                                   <TextFieldOutline
                                     top="0"
                                     left="0"
                                     borderTop="10"
                                     borderBottom="10"
                                     enterBorderColor="rgba(255,0,0,0.8)"
                                     downBorderColor="rgba(255,0,0,0.6)"
                                     borderColor="rgba(0,0,0,0.2)"
                                     value={item.dateValue}
                                     disabled={state.showProgress}
                                     onChange={event =>
                                       i
                                       |> changeItemDate(
                                            ReactEvent.Form.target(event)##value,
                                          )
                                     }>
                                     null
                                   </TextFieldOutline>
                                 | _ =>
                                   <>
                                     <SelectOutline
                                       top="0"
                                       left="0"
                                       enterBorderColor="rgba(255,0,0,0.8)"
                                       downBorderColor="rgba(255,0,0,0.6)"
                                       borderColor="rgba(0,0,0,0.2)"
                                       value={item.dateValue}
                                       disabled={state.showProgress}
                                       onClick={_ => i |> showDateMenu}>
                                       ...(
                                            item.showDateMenu
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
                                                  {item.dateitems
                                                   |> Array.map(dateitem =>
                                                        <MenuItem
                                                          top="0"
                                                          right="8"
                                                          bottom="0"
                                                          left="8"
                                                          disablePadding={
                                                                    dateitem.
                                                                    optionPadding
                                                                    }
                                                          topLeft="12"
                                                          topRight="12"
                                                          bottomRight="12"
                                                          bottomLeft="12"
                                                          onClick={_ =>
                                                            i
                                                            |> clickDateMenu(
                                                                 dateitem.
                                                                   value,
                                                               )
                                                          }>
                                                          {dateitem.value
                                                           |> string}
                                                        </MenuItem>
                                                      )
                                                   |> array}
                                                </SelectMenu>
                                              : null,
                                            <IconGeneral
                                              animation={
                                                item.showDateMenu
                                                |> topDownRorate
                                              }
                                              src=arrowDownBlack
                                            />,
                                          )
                                     </SelectOutline>
                                     <BackgroundBoard
                                       showBackground={item.showDateMenu}
                                       backgroundColor="transparent"
                                       onClick={_ => i |> showDateMenu}
                                     />
                                   </>
                                 };
                               }
                               : null}
                          </GridItem>
                          <GridItem
                            top="0" right="0" bottom="0" left="0" xs="auto">
                            {item.showSttime
                               ? {
                                 switch (item.sttimeOutValue) {
                                 | "label" =>
                                   <Typography
                                     variant="subtitle2"
                                     style={ReactDOMRe.Style.make(
                                       ~paddingLeft="6px",
                                       ~paddingRight="6px",
                                       (),
                                     )}
                                     noWrap=true>
                                     {item.sttimeValue |> string}
                                   </Typography>
                                 | "image" =>
                                   <ImageUpload
                                     webLoad={state.showProgress}
                                     showDrop={item.showSttimeDrop}
                                     showFile={item.showSttimeFile}
                                     src={item.sttimeValue}
                                     fileRef
                                     onDragOver={event =>
                                       i |> dragOverSttime(event)
                                     }
                                     onDragLeave={event =>
                                       i |> dragLeaveSttime(event)
                                     }
                                     onDrop={event =>
                                       i
                                       |> dropItemSttime(
                                            event,
                                            ReactEventRe.Synthetic.nativeEvent(
                                              event,
                                            )##dataTransfer##files[0],
                                          )
                                     }
                                     disabled={state.showProgress}
                                     onClick=chooseFile
                                     onChange={event =>
                                       i
                                       |> uploadItemSttime(
                                            ReactEvent.Form.target(event)##files[0],
                                          )
                                     }
                                   />
                                 | "text" =>
                                   <TextFieldOutline
                                     width="50"
                                     top="0"
                                     left="0"
                                     borderTop="10"
                                     borderBottom="10"
                                     enterBorderColor="rgba(255,0,0,0.8)"
                                     downBorderColor="rgba(255,0,0,0.6)"
                                     borderColor="rgba(0,0,0,0.2)"
                                     value={item.sttimeValue}
                                     disabled={state.showProgress}
                                     onChange={event =>
                                       i
                                       |> changeItemSttime(
                                            ReactEvent.Form.target(event)##value,
                                          )
                                     }>
                                     null
                                   </TextFieldOutline>
                                 | "textarea" =>
                                   <TextFieldOutline
                                     top="0"
                                     left="0"
                                     borderTop="10"
                                     borderBottom="10"
                                     enterBorderColor="rgba(255,0,0,0.8)"
                                     downBorderColor="rgba(255,0,0,0.6)"
                                     borderColor="rgba(0,0,0,0.2)"
                                     value={item.sttimeValue}
                                     disabled={state.showProgress}
                                     onChange={event =>
                                       i
                                       |> changeItemSttime(
                                            ReactEvent.Form.target(event)##value,
                                          )
                                     }>
                                     null
                                   </TextFieldOutline>
                                 | _ =>
                                   <>
                                     <SelectOutline
                                       top="0"
                                       left="0"
                                       enterBorderColor="rgba(255,0,0,0.8)"
                                       downBorderColor="rgba(255,0,0,0.6)"
                                       borderColor="rgba(0,0,0,0.2)"
                                       value={item.sttimeValue}
                                       disabled={state.showProgress}
                                       onClick={_ => i |> showSttimeMenu}>
                                       ...(
                                            item.showSttimeMenu
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
                                                  {item.sttimeitems
                                                   |> Array.map(fsttimeitem =>
                                                        <MenuItem
                                                          top="0"
                                                          right="8"
                                                          bottom="0"
                                                          left="8"
                                                          disablePadding={
                                                                    fsttimeitem.
                                                                    optionPadding
                                                                    }
                                                          topLeft="12"
                                                          topRight="12"
                                                          bottomRight="12"
                                                          bottomLeft="12"
                                                          onClick={_ =>
                                                            i
                                                            |> clickSttimeMenu(
                                                                 fsttimeitem.
                                                                   value,
                                                               )
                                                          }>
                                                          {fsttimeitem.value
                                                           |> string}
                                                        </MenuItem>
                                                      )
                                                   |> array}
                                                </SelectMenu>
                                              : null,
                                            <IconGeneral
                                              animation={
                                                item.showSttimeMenu
                                                |> topDownRorate
                                              }
                                              src=arrowDownBlack
                                            />,
                                          )
                                     </SelectOutline>
                                     <BackgroundBoard
                                       showBackground={item.showSttimeMenu}
                                       backgroundColor="transparent"
                                       onClick={_ => i |> showSttimeMenu}
                                     />
                                   </>
                                 };
                               }
                               : null}
                          </GridItem>
                          <GridItem
                            top="0" right="0" bottom="0" left="0" xs="auto">
                            {item.showEntime
                               ? {
                                 switch (item.entimeOutValue) {
                                 | "label" =>
                                   <Typography
                                     variant="subtitle2"
                                     style={ReactDOMRe.Style.make(
                                       ~paddingLeft="6px",
                                       ~paddingRight="6px",
                                       (),
                                     )}
                                     noWrap=true>
                                     {item.entimeValue |> string}
                                   </Typography>
                                 | "image" =>
                                   <ImageUpload
                                     webLoad={state.showProgress}
                                     showDrop={item.showEntimeDrop}
                                     showFile={item.showEntimeFile}
                                     src={item.sttimeValue}
                                     fileRef
                                     onDragOver={event =>
                                       i |> dragOverEntime(event)
                                     }
                                     onDragLeave={event =>
                                       i |> dragLeaveEntime(event)
                                     }
                                     onDrop={event =>
                                       i
                                       |> dropItemEntime(
                                            event,
                                            ReactEventRe.Synthetic.nativeEvent(
                                              event,
                                            )##dataTransfer##files[0],
                                          )
                                     }
                                     disabled={state.showProgress}
                                     onClick=chooseFile
                                     onChange={event =>
                                       i
                                       |> uploadItemEntime(
                                            ReactEvent.Form.target(event)##files[0],
                                          )
                                     }
                                   />
                                 | "text" =>
                                   <TextFieldOutline
                                     width="50"
                                     top="0"
                                     left="0"
                                     borderTop="10"
                                     borderBottom="10"
                                     enterBorderColor="rgba(255,0,0,0.8)"
                                     downBorderColor="rgba(255,0,0,0.6)"
                                     borderColor="rgba(0,0,0,0.2)"
                                     value={item.entimeValue}
                                     disabled={state.showProgress}
                                     onChange={event =>
                                       i
                                       |> changeItemEntime(
                                            ReactEvent.Form.target(event)##value,
                                          )
                                     }>
                                     null
                                   </TextFieldOutline>
                                 | "textarea" =>
                                   <TextFieldOutline
                                     top="0"
                                     left="0"
                                     borderTop="10"
                                     borderBottom="10"
                                     enterBorderColor="rgba(255,0,0,0.8)"
                                     downBorderColor="rgba(255,0,0,0.6)"
                                     borderColor="rgba(0,0,0,0.2)"
                                     value={item.entimeValue}
                                     disabled={state.showProgress}
                                     onChange={event =>
                                       i
                                       |> changeItemEntime(
                                            ReactEvent.Form.target(event)##value,
                                          )
                                     }>
                                     null
                                   </TextFieldOutline>
                                 | _ =>
                                   <>
                                     <SelectOutline
                                       top="0"
                                       left="0"
                                       enterBorderColor="rgba(255,0,0,0.8)"
                                       downBorderColor="rgba(255,0,0,0.6)"
                                       borderColor="rgba(0,0,0,0.2)"
                                       value={item.entimeValue}
                                       disabled={state.showProgress}
                                       onClick={_ => i |> showEntimeMenu}>
                                       ...(
                                            item.showEntimeMenu
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
                                                  {item.entimeitems
                                                   |> Array.map(fentimeitem =>
                                                        <MenuItem
                                                          top="0"
                                                          right="8"
                                                          bottom="0"
                                                          left="8"
                                                          disablePadding={
                                                                    fentimeitem.
                                                                    optionPadding
                                                                    }
                                                          topLeft="12"
                                                          topRight="12"
                                                          bottomRight="12"
                                                          bottomLeft="12"
                                                          onClick={_ =>
                                                            i
                                                            |> clickEntimeMenu(
                                                                 fentimeitem.
                                                                   value,
                                                               )
                                                          }>
                                                          {fentimeitem.value
                                                           |> string}
                                                        </MenuItem>
                                                      )
                                                   |> array}
                                                </SelectMenu>
                                              : null,
                                            <IconGeneral
                                              animation={
                                                item.showEntimeMenu
                                                |> topDownRorate
                                              }
                                              src=arrowDownBlack
                                            />,
                                          )
                                     </SelectOutline>
                                     <BackgroundBoard
                                       showBackground={item.showEntimeMenu}
                                       backgroundColor="transparent"
                                       onClick={_ => i |> showEntimeMenu}
                                     />
                                   </>
                                 };
                               }
                               : null}
                          </GridItem>
                          <GridItem
                            style={ReactDOMRe.Style.make(~height="32px", ())}
                            top="0"
                            right="0"
                            bottom="0"
                            left="0"
                            width="32px"
                            xs="no">
                            {item.showEnter
                               ? <IconButton
                                   enterBackgroundColor="transparent"
                                   downBackgroundColor="transparent"
                                   padding="4"
                                   disabled={state.showProgress}>
                                   <IconAction
                                     animation="leftRight"
                                     src=createBlack
                                   />
                                 </IconButton>
                               : null}
                          </GridItem>
                        </GridContainer>
                      </div>
                    </GridItem>
                  )
               |> array}
            </GridContainer>
          </GridItem>
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
