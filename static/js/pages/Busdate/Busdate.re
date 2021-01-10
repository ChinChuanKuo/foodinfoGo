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

type answeritem = {
  id: int,
  value: string,
  showAnswer: bool,
};

type item = {
  wkId: int,
  weekId: string,
  showWeek: bool,
  weekOutValue: string,
  weekChecked: bool,
  showWeekDrop: bool,
  showWeekFile: bool,
  weekValue: string,
  showWeekMenu: bool,
  weekitems: array(optionitem),
  weekanswitems: array(answeritem),
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
  | ShowWeekDrop(bool, int)
  | ShowWeekFile(string, int)
  | ChangeItemWeek(string, int)
  | ShowWeekMenu(int)
  | ClickWeekMenu(string, int)
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
  | ShowMoreForm(int)
  | DeleteWeekForm(int)
  | RefreshWeekForm
  | AddWeekForm(array(item))
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
  | ShowWeekDrop(droped, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) => index == i ? {...item, showWeekDrop: droped} : item,
          state.items,
        ),
    }
  | ShowWeekFile(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                weekValue: value,
                showWeekFile: !item.showWeekFile,
                itemModify: true,
              }
              : item,
          state.items,
        ),
    }
  | ChangeItemWeek(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, weekValue: value, itemModify: true} : item,
          state.items,
        ),
    }
  | ShowWeekMenu(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showWeekMenu: !item.showWeekMenu} : item,
          state.items,
        ),
    }
  | ClickWeekMenu(value, index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i
              ? {
                ...item,
                weekValue: value,
                showWeekMenu: !item.showWeekMenu,
                itemModify: true,
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
                itemModify: true,
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
              ? {...item, sttimeValue: value, itemModify: true} : item,
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
                itemModify: true,
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
                itemModify: true,
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
              ? {...item, entimeValue: value, itemModify: true} : item,
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
                itemModify: true,
              }
              : item,
          state.items,
        ),
    }
  | ShowMoreForm(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, showMore: !item.showMore} : item,
          state.items,
        ),
    }
  | DeleteWeekForm(index) => {
      ...state,
      items:
        Array.mapi(
          (i, item) =>
            index == i ? {...item, itemDelete: !item.itemDelete} : item,
          state.items,
        ),
    }
  | RefreshWeekForm => {
      ...state,
      items:
        Js_array.filter(
          (item: item) => item.itemDelete !== true,
          state.items,
        ),
    }
  | AddWeekForm(items) => {
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
  index: 2,
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
      |> Axiosapi.Busdate.search
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

  let upWeekAJax = (file, i) => {
    let formData = FormData.make();
    FormData.append(formData, "file", file) |> ignore;
    Js.Promise.(
      formData
      |> Files.upload
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               ShowWeekFile(response##data##file, i) |> dispatch;
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

  let dragOverWeek =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowWeekDrop(true, i) |> dispatch;
    });

  let dragLeaveWeek =
    useCallback((event, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ShowWeekDrop(false, i) |> dispatch;
    });

  let dropItemWeek =
    useCallback((event, value, i) => {
      ReactEventRe.Mouse.preventDefault(event);
      ReactEventRe.Mouse.stopPropagation(event);
      ActionShowProgress |> dispatch;
      ShowWeekDrop(false, i) |> dispatch;
      i |> upWeekAJax(value);
    });

  let uploadItemWeek =
    useCallback((value, i) => {
      ActionShowProgress |> dispatch;
      i |> upWeekAJax(value);
    });

  let changeItemWeek =
    useCallback((value, i) => ChangeItemWeek(value, i) |> dispatch);

  let showWeekMenu = useCallback(i => ShowWeekMenu(i) |> dispatch);

  let clickWeekMenu =
    useCallback((value, i) => ClickWeekMenu(value, i) |> dispatch);

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

  let showMoreForm = useCallback(i => ShowMoreForm(i) |> dispatch);

  let copyWeekForm = useCallback(i => ActionShowProgress |> dispatch);

  let deleteWeekForm = useCallback(i => DeleteWeekForm(i) |> dispatch);

  let addWeekAJax = () =>
    Js.Promise.(
      iItemsData(state.items, "newid" |> Locals.select)
      |> Axiosapi.Busdate.addWeek
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               AddWeekForm(response##data##items) |> dispatch;
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

  let addWeekItem =
    useCallback(_ => {
      ActionShowProgress |> dispatch;
      addWeekAJax();
    });

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
          (item: item) =>
            item.itemModify === true || item.itemDelete === true,
          state.items,
        ),
        "newid" |> Locals.select,
      )
      |> Axiosapi.Busdate.insert
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               RefreshWeekForm |> dispatch;
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
            <Button
              width="100%"
              enterBackgroundColor="rgba(255,0,0,0.8)"
              downBackgroundColor="rgba(255,0,0,0.6)"
              backgroundColor="rgba(255,0,0,0.8)"
              size="large"
              disabled={state.showProgress}
              onClick=addWeekItem>
              <FormattedMessage
                id="Busdate.busniess"
                defaultMessage="Busniess"
              />
            </Button>
          </GridItem>
          <GridItem
            style={ReactDOMRe.Style.make(
              ~position="sticky",
              ~top="56px",
              ~zIndex="1000",
              (),
            )}
            top="0"
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
            </GridContainer>
          </GridItem>
          <GridItem top="0" right="24" left="24" xs="auto">
            <GridContainer
              direction="column" justify="center" alignItem="stretch">
              {state.items
               |> Array.mapi((i, item) =>
                    <GridItem right="0" left="0" xs="auto">
                      <GridContainer
                        direction="row" justify="start" alignItem="center">
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          {item.showWeek
                             ? {
                               switch (item.weekOutValue) {
                               | "label" =>
                                 <Typography variant="subtitle2" noWrap=true>
                                   {item.weekValue |> string}
                                 </Typography>
                               | "image" =>
                                 <ImageUpload
                                   webLoad={state.showProgress}
                                   showDrop={item.showWeekDrop}
                                   showFile={item.showWeekFile}
                                   src={item.weekValue}
                                   fileRef
                                   onDragOver={event =>
                                     dragOverWeek(event, i)
                                   }
                                   onDragLeave={event =>
                                     dragLeaveWeek(event, i)
                                   }
                                   onDrop={event =>
                                     i
                                     |> dropItemWeek(
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
                                     |> uploadItemWeek(
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
                                   value={item.weekValue}
                                   disabled={
                                     state.showProgress || item.itemDelete
                                   }
                                   onChange={event =>
                                     i
                                     |> changeItemWeek(
                                          ReactEvent.Form.target(event)##value,
                                        )
                                   }>
                                   null
                                 </TextFieldOutline>
                               | "textline" =>
                                 <TextFieldOutline
                                   top="0"
                                   left="0"
                                   borderTop="10"
                                   borderBottom="10"
                                   enterBorderColor="rgba(255,0,0,0.8)"
                                   downBorderColor="rgba(255,0,0,0.6)"
                                   borderColor="rgba(0,0,0,0.2)"
                                   value={item.weekValue}
                                   disabled={
                                     state.showProgress || item.itemDelete
                                   }
                                   onChange={event =>
                                     i
                                     |> changeItemWeek(
                                          ReactEvent.Form.target(event)##value,
                                        )
                                   }>
                                   null
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
                                   value={item.weekValue}
                                   disabled={
                                     state.showProgress || item.itemDelete
                                   }
                                   onChange={event =>
                                     i
                                     |> changeItemWeek(
                                          ReactEvent.Form.target(event)##value,
                                        )
                                   }>
                                   null
                                 </TextFieldMultiline>
                               | _ =>
                                 <>
                                   <SelectOutline
                                     top="0"
                                     left="0"
                                     enterBorderColor="rgba(255,0,0,0.8)"
                                     downBorderColor="rgba(255,0,0,0.6)"
                                     borderColor="rgba(0,0,0,0.2)"
                                     value={item.weekValue}
                                     disabled={
                                       state.showProgress || item.itemDelete
                                     }
                                     onClick={_ => i |> showWeekMenu}>
                                     ...(
                                          item.showWeekMenu
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
                                                {item.weekitems
                                                 |> Array.map(weekitem =>
                                                      <MenuItem
                                                        top="0"
                                                        right="8"
                                                        bottom="0"
                                                        left="8"
                                                        disablePadding={
                                                                    weekitem.
                                                                    optionPadding
                                                                    }
                                                        topLeft="12"
                                                        topRight="12"
                                                        bottomRight="12"
                                                        bottomLeft="12"
                                                        onClick={_ =>
                                                          i
                                                          |> clickWeekMenu(
                                                               weekitem.value,
                                                             )
                                                        }>
                                                        {weekitem.value
                                                         |> string}
                                                      </MenuItem>
                                                    )
                                                 |> array}
                                              </SelectMenu>
                                            : null,
                                          <IconGeneral
                                            animation={
                                              item.showWeekMenu
                                              |> topDownRorate
                                            }
                                            src=arrowDownBlack
                                          />,
                                        )
                                   </SelectOutline>
                                   <BackgroundBoard
                                     showBackground={item.showWeekMenu}
                                     backgroundColor="transparent"
                                     onClick={_ => i |> showWeekMenu}
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
                                   disabled={
                                     state.showProgress || item.itemDelete
                                   }
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
                                   disabled={
                                     state.showProgress || item.itemDelete
                                   }
                                   onChange={event =>
                                     i
                                     |> changeItemSttime(
                                          ReactEvent.Form.target(event)##value,
                                        )
                                   }>
                                   null
                                 </TextFieldOutline>
                               | "textline" =>
                                 <TextFieldOutline
                                   top="0"
                                   left="0"
                                   borderTop="10"
                                   borderBottom="10"
                                   enterBorderColor="rgba(255,0,0,0.8)"
                                   downBorderColor="rgba(255,0,0,0.6)"
                                   borderColor="rgba(0,0,0,0.2)"
                                   value={item.sttimeValue}
                                   disabled={
                                     state.showProgress || item.itemDelete
                                   }
                                   onChange={event =>
                                     i
                                     |> changeItemSttime(
                                          ReactEvent.Form.target(event)##value,
                                        )
                                   }>
                                   null
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
                                   value={item.sttimeValue}
                                   disabled={
                                     state.showProgress || item.itemDelete
                                   }
                                   onChange={event =>
                                     i
                                     |> changeItemSttime(
                                          ReactEvent.Form.target(event)##value,
                                        )
                                   }>
                                   null
                                 </TextFieldMultiline>
                               | _ =>
                                 <>
                                   <SelectOutline
                                     top="0"
                                     left="0"
                                     enterBorderColor="rgba(255,0,0,0.8)"
                                     downBorderColor="rgba(255,0,0,0.6)"
                                     borderColor="rgba(0,0,0,0.2)"
                                     value={item.sttimeValue}
                                     disabled={
                                       state.showProgress || item.itemDelete
                                     }
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
                                                 |> Array.map(wsttimeitem =>
                                                      <MenuItem
                                                        top="0"
                                                        right="8"
                                                        bottom="0"
                                                        left="8"
                                                        disablePadding={
                                                                    wsttimeitem.
                                                                    optionPadding
                                                                    }
                                                        topLeft="12"
                                                        topRight="12"
                                                        bottomRight="12"
                                                        bottomLeft="12"
                                                        onClick={_ =>
                                                          i
                                                          |> clickSttimeMenu(
                                                               wsttimeitem.
                                                                 value,
                                                             )
                                                        }>
                                                        {wsttimeitem.value
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
                                   src={item.entimeValue}
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
                                   disabled={
                                     state.showProgress || item.itemDelete
                                   }
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
                                   disabled={
                                     state.showProgress || item.itemDelete
                                   }
                                   onChange={event =>
                                     i
                                     |> changeItemEntime(
                                          ReactEvent.Form.target(event)##value,
                                        )
                                   }>
                                   null
                                 </TextFieldOutline>
                               | "textline" =>
                                 <TextFieldOutline
                                   top="0"
                                   left="0"
                                   borderTop="10"
                                   borderBottom="10"
                                   enterBorderColor="rgba(255,0,0,0.8)"
                                   downBorderColor="rgba(255,0,0,0.6)"
                                   borderColor="rgba(0,0,0,0.2)"
                                   value={item.entimeValue}
                                   disabled={
                                     state.showProgress || item.itemDelete
                                   }
                                   onChange={event =>
                                     i
                                     |> changeItemEntime(
                                          ReactEvent.Form.target(event)##value,
                                        )
                                   }>
                                   null
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
                                   value={item.entimeValue}
                                   disabled={
                                     state.showProgress || item.itemDelete
                                   }
                                   onChange={event =>
                                     i
                                     |> changeItemEntime(
                                          ReactEvent.Form.target(event)##value,
                                        )
                                   }>
                                   null
                                 </TextFieldMultiline>
                               | _ =>
                                 <>
                                   <SelectOutline
                                     top="0"
                                     left="0"
                                     enterBorderColor="rgba(255,0,0,0.8)"
                                     downBorderColor="rgba(255,0,0,0.6)"
                                     borderColor="rgba(0,0,0,0.2)"
                                     value={item.entimeValue}
                                     disabled={
                                       state.showProgress || item.itemDelete
                                     }
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
                                                 |> Array.map(wentimeitem =>
                                                      <MenuItem
                                                        top="0"
                                                        right="8"
                                                        bottom="0"
                                                        left="8"
                                                        disablePadding={
                                                                    wentimeitem.
                                                                    optionPadding
                                                                    }
                                                        topLeft="12"
                                                        topRight="12"
                                                        bottomRight="12"
                                                        bottomLeft="12"
                                                        onClick={_ =>
                                                          i
                                                          |> clickEntimeMenu(
                                                               wentimeitem.
                                                                 value,
                                                             )
                                                        }>
                                                        {wentimeitem.value
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
                            style={ReactDOMRe.Style.make(
                              ~position="absolute",
                              ~bottom="-6px",
                              ~left="-6px",
                              (),
                            )}
                            padding="6"
                            onClick={_ => i |> showMoreForm}>
                            <Tooltip
                              location="bottom"
                              backgroundColor="rgba(255,0,0,0.8)">
                              <FormattedMessage
                                id="more"
                                defaultMessage="More"
                              />
                            </Tooltip>
                            <IconAction
                              style=zIndexGrow
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
                                     bottomLeft="12"
                                     onClick={_ => i |> copyWeekForm}>
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
                                     onClick={_ => i |> deleteWeekForm}>
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
                                               ? refreshBlack : deleteBlack
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
                                   onClick={_ => i |> showMoreForm}
                                 />
                               </>
                             : null}
                        </GridItem>
                      </GridContainer>
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
