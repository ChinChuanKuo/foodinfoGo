open React;
open Together;
open ReactIntl;
open Icons;
open Data;
open Items;
open Axiosapi;
open Storage;
[%bs.raw {|require('../../../scss/pages/Together/together.scss')|}];

type chatitem = {
  id: string,
  fstName: string,
  content: string,
  datetime: string,
  name: string,
  itemDelete: bool,
  showEnter: bool,
};

type menuitem = {
  id: string,
  name: string,
  price: string,
  allergy: string,
  album: string,
  remark: string,
};

type formitem = {
  type_: string,
  phone: string,
  address: string,
  menuitems: array(menuitem),
};

type item = {
  id: string,
  tile: string,
  desc: string,
  distance: string,
  arrival: string,
  enter: bool,
};

type state = {
  formLoad: bool,
  showProgress: bool,
  error: bool,
  insert: bool,
  update: bool,
  delete: bool,
  export: bool,
  showItem: bool,
  items: array(item),
  showFull: bool,
  formId: string,
  tabitems: list(tabitem),
  index: int,
  formTile: string,
  formDesc: string,
  formitems: array(formitem),
  chatitems: array(chatitem),
  showYoutube: bool,
  youtubeText: string,
};

type action =
  | SettingError
  | SettingFormLoad
  | ActionShowProgress
  | ActionPermissItems(bool, bool, bool, bool)
  | SettingFormPolls(array(item))
  | SettingFormItems(bool, array(item))
  | SettingScrollItems(bool, array(item))
  | MouseFormItem(int)
  | SettingFullPolls(array(formitem))
  | ShowAnimationFull(string, string, string, array(formitem))
  | ClickItemTab(int)
  | MouseChatItem(int)
  | AddChatItems(array(chatitem))
  | CloseAnimationFull
  | ActionSnackBar(string, bool);

let reducer = (state, action) =>
  switch (action) {
  | SettingError => {...state, error: !state.error}
  | SettingFormLoad => {...state, formLoad: !state.formLoad}
  | ActionShowProgress => {...state, showProgress: !state.showProgress}
  | ActionPermissItems(insert, update, delete, export) => {
      ...state,
      insert,
      update,
      delete,
      export,
    }
  | SettingFormPolls(items) => {...state, items}
  | SettingFormItems(showItem, items) => {...state, showItem, items}
  | SettingScrollItems(showItem, items) => {
      ...state,
      showItem,
      items: Array.append(state.items, items),
    }
  | MouseFormItem(index) => {
      ...state,
      items:
        Array.mapi((i, item) => {...item, enter: index == i}, state.items),
    }
  | SettingFullPolls(items) => {...state, formitems: items}
  | ShowAnimationFull(id, tile, desc, items) => {
      ...state,
      formId: id,
      formTile: tile,
      formDesc: desc,
      formitems: items,
      showFull: !state.showFull,
    }
  | ClickItemTab(index) => {
      ...state,
      tabitems:
        List.mapi(
          (i, tabitem) => {...tabitem, showTab: index == i},
          state.tabitems,
        ),
      index,
    }
  | MouseChatItem(index) => {
      ...state,
      chatitems:
        Array.mapi(
          (i, chatitem) => {...chatitem, showEnter: index == i},
          state.chatitems,
        ),
    }
  | AddChatItems(items) => {
      ...state,
      chatitems: Array.append(state.chatitems, items),
    }
  | CloseAnimationFull => {...state, showFull: !state.showFull}
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
  showItem: false,
  items: [||],
  showFull: false,
  formId: "",
  tabitems: [
    {showTab: true, tabImage: storeBlack},
    {showTab: false, tabImage: menuBookBlack},
    {showTab: false, tabImage: mapBlack},
  ],
  index: 0,
  formTile: "",
  formDesc: "",
  formitems: [||],
  chatitems: [||],
  showYoutube: false,
  youtubeText: "",
};

[@react.component]
let make = _ => {
  let (state, dispatch) = useReducer(reducer, initialState);

  let textRef = useRef(Js.Nullable.null);

  let barShowRestoreAction = youtubeText => {
    ActionSnackBar(youtubeText, true) |> dispatch;
    Js.Global.setTimeout(() => ActionSnackBar("", false) |> dispatch, 5000)
    |> ignore;
  };

  let pollingAJax = () =>
    Js.Promise.(
      sLocalData(
        "longitude" |> Locals.select,
        "latitude" |> Locals.select,
        state.items |> Js_array.length,
        "newid" |> Locals.select,
      )
      |> Default.polling
      |> then_(response =>
           SettingFormPolls(response##data##items) |> dispatch |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let searchAJax = () =>
    Js.Promise.(
      sLocalData(
        "longitude" |> Locals.select,
        "latitude" |> Locals.select,
        state.items |> Js_array.length,
        "newid" |> Locals.select,
      )
      |> Default.search
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               SettingFormItems(
                 response##data##showItem,
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
             searchAJax();
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  useEffect(() =>
    switch (state.formLoad, state.showFull) {
    | (true, true) => Some(() => "action" |> Js.log)
    | (true, false) =>
      let inteId = Js.Global.setTimeout(() => pollingAJax(), 3000);
      Some(() => inteId |> Js.Global.clearTimeout);
    | (false, _) =>
      let testtime = SettingFormLoad |> dispatch;
      let timeId = permissAJax();
      Some(
        () => {
          testtime;
          timeId;
        },
      );
    }
  );

  let scrollAJax = length =>
    Js.Promise.(
      sLocalData(
        "longitude" |> Locals.select,
        "latitude" |> Locals.select,
        length,
        "newid" |> Locals.select,
      )
      |> Default.scroll
      |> then_(response =>
           {
             SettingScrollItems(
               response##data##showItem,
               response##data##items,
             )
             |> dispatch;
             ActionShowProgress |> dispatch;
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let scrollBar =
    useCallback(_ => {
      ActionShowProgress |> dispatch;
      state.items |> Js_array.length |> scrollAJax;
    });

  let mouseFormItem = useCallback(i => MouseFormItem(i) |> dispatch);

  let pingItemFunc: (int, int) => unit = [%bs.raw
    (length, count) => {| if (state.index == 0) { pingItemAJax(length + count); } |}
  ];

  let pingItemEror: int => unit = [%bs.raw
    length => {| if (state.index == 0) { setTimeout(() => pingItemAJax(length), 15000); } |}
  ];

  let pingItemAJax = length =>
    Js.Promise.(
      sPChatData(state.formId, length, "newid" |> Locals.select)
      |> Default.pingItem
      |> then_(response =>
           {
             SettingFullPolls(response##data##items) |> dispatch;
             response##data##items |> Js_array.length |> pingItemFunc(length);
           }
           |> resolve
         )
      |> catch(_ => length |> pingItemEror |> resolve)
      |> ignore
    );

  let sItemAJax = id =>
    Js.Promise.(
      dFormData(id, "newid" |> Locals.select)
      |> Default.sItem
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               ShowAnimationFull(
                 response##data##formId,
                 response##data##tile,
                 response##data##desc,
                 response##data##items,
               )
               |> dispatch;
               ActionShowProgress |> dispatch;
               response##data##items |> Js_array.length |> pingItemAJax;
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

  let clickFormBoard =
    useCallback(id => {
      ActionShowProgress |> dispatch;
      id |> sItemAJax;
    });

  let pingChatFunc: (int, int) => unit = [%bs.raw
    (length, count) => {| if (state.index == 1) { pingChatAJax(length + count); } |}
  ];

  let pingChatEror: int => unit = [%bs.raw
    length => {| if (state.index == 1) { setTimeout(() => pingChatAJax(length), 15000); } |}
  ];

  let pingChatAJax = length =>
    Js.Promise.(
      sPChatData(state.formId, length, "newid" |> Locals.select)
      |> Default.pingChat
      |> then_(response =>
           {
             AddChatItems(response##data##items) |> dispatch;
             response##data##items |> Js_array.length |> pingChatFunc(length);
           }
           |> resolve
         )
      |> catch(_ => length |> pingChatEror |> resolve)
      |> ignore
    );

  let sChatAJax = () =>
    Js.Promise.(
      sPChatData(
        state.formId,
        Js_array.length(state.chatitems),
        "newid" |> Locals.select,
      )
      |> Default.sChat
      |> then_(response => {
           (
             switch (response##data##status) {
             | "istrue" =>
               AddChatItems(response##data##items) |> dispatch;
               ActionShowProgress |> dispatch;
               response##data##items |> Js_array.length |> pingChatAJax;
             | _ => ActionShowProgress |> dispatch
             }
           )
           |> resolve
         })
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let clickItemTab =
    useCallback(i => {
      ClickItemTab(i) |> dispatch;
      if (i == 1) {
        ActionShowProgress |> dispatch;
        sChatAJax();
      };
    });

  let mouseChatItem = useCallback(i => MouseChatItem(i) |> dispatch);

  let closeAnimationFull = useCallback(_ => CloseAnimationFull |> dispatch);

  <>
    <NewFacebook showProgress={state.showProgress} error={state.error}>
      ...(
           <GridItem
             style=marginAuto
             top="0"
             right="32"
             bottom="0"
             left="32"
             xs="12"
             maxWidth="770px">
             <GridContainer
               direction="column" justify="center" alignItem="stretch">
               {state.items
                |> Array.mapi((i, item) =>
                     <div
                       onMouseEnter={_ => i |> mouseFormItem}
                       onMouseLeave={_ => (-1) |> mouseFormItem}
                       onClick={_ => item.id |> clickFormBoard}>
                       <GridItem
                         top="0"
                         right="0"
                         bottom="0"
                         left="0"
                         cursor="pointer"
                         enterBorderRadius="10"
                         borderRadius="10"
                         enterBackgroundColor="rgba(0,0,0,0.1)"
                         xs="auto">
                         <GridContainer
                           backgroundColor="none"
                           direction="column"
                           justify="center"
                           alignItem="stretch">
                           <GridItem
                             enterBackgroundColor="none"
                             backgroundColor="none"
                             xs="auto">
                             <GridContainer
                               backgroundColor="none"
                               direction="row"
                               justify="between"
                               alignItem="center">
                               <GridItem
                                 top="0"
                                 right="0"
                                 bottom="0"
                                 left="0"
                                 enterBackgroundColor="none"
                                 backgroundColor="none"
                                 xs="no">
                                 <Typography variant="tile" fontWeight="600">
                                   {item.tile |> string}
                                 </Typography>
                               </GridItem>
                               <GridItem
                                 top="0"
                                 right="0"
                                 bottom="0"
                                 left="0"
                                 enterBackgroundColor="none"
                                 backgroundColor="none"
                                 xs="no">
                                 {item.enter
                                    ? <IconButton padding="6">
                                        <Tooltip
                                          location="right"
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
                                    : <div
                                        style={ReactDOMRe.Style.make(
                                          ~width="36px",
                                          ~height="36px",
                                          (),
                                        )}
                                      />}
                               </GridItem>
                             </GridContainer>
                           </GridItem>
                           <GridItem
                             top="0"
                             enterBackgroundColor="none"
                             backgroundColor="none"
                             xs="auto">
                             <GridContainer
                               backgroundColor="none"
                               direction="row"
                               justify="between"
                               alignItem="center">
                               <GridItem
                                 top="0"
                                 right="0"
                                 bottom="0"
                                 left="0"
                                 enterBackgroundColor="none"
                                 backgroundColor="none"
                                 xs="no">
                                 <Typography
                                   variant="subheading" color="#606060">
                                   {item.distance |> string}
                                 </Typography>
                               </GridItem>
                               <GridItem
                                 top="0"
                                 right="0"
                                 bottom="0"
                                 left="0"
                                 enterBackgroundColor="none"
                                 backgroundColor="none"
                                 xs="no">
                                 <Typography
                                   variant="subheading" color="#606060">
                                   {item.arrival |> string}
                                 </Typography>
                               </GridItem>
                             </GridContainer>
                           </GridItem>
                           <GridItem
                             top="0"
                             enterBackgroundColor="none"
                             backgroundColor="none"
                             xs="auto">
                             <Typography variant="subheading">
                               {item.desc |> string}
                             </Typography>
                           </GridItem>
                         </GridContainer>
                       </GridItem>
                       <GridItem
                         enterBackgroundColor="none"
                         backgroundColor="none"
                         xs="auto">
                         <Divider />
                       </GridItem>
                     </div>
                   )
                |> array}
             </GridContainer>
             <BottomScroll
               showBar={state.showItem}
               disabled={state.showProgress}
               onClick=scrollBar
             />
           </GridItem>,
           null,
         )
    </NewFacebook>
    <DialogFull showAnimation={state.showFull}>
      <DialogTitle top="18" left="64">
        <Typography variant="headline" fontWeight="600">
          {state.formTile |> string}
        </Typography>
      </DialogTitle>
      <DialogContent>
        <DialogContentText>
          <GridItem
            style=marginAuto
            top="0"
            right="0"
            bottom="0"
            left="54"
            xs="12"
            maxWidth="770px">
            <GridContainer
              direction="column" justify="center" alignItem="stretch">
              <GridItem
                style={ReactDOMRe.Style.make(
                  ~position="sticky",
                  ~top="0px",
                  ~zIndex="1000",
                  (),
                )}
                top="0"
                right="0"
                bottom="6"
                left="0"
                xs="auto">
                <Tabs id="default-" index={state.index} short=20 height="3">
                  {state.tabitems
                   |> List.mapi((i, tabitem) =>
                        <Tab
                          showTab={tabitem.showTab}
                          maxWidth="111.6"
                          borderRadius="15"
                          id={"default-" ++ string_of_int(i)}
                          animationName="none"
                          onClick={_ => i |> clickItemTab}>
                          <IconAction
                            width="28"
                            height="28"
                            animation="leftRight"
                            src={tabitem.tabImage}
                          />
                        </Tab>
                      )
                   |> Array.of_list
                   |> array}
                </Tabs>
              </GridItem>
              {switch (state.index) {
               | 0 =>
                 state.formitems
                 |> Array.map(formitem =>
                      <>
                        <GridItem
                          top="6" right="0" bottom="0" left="0" xs="auto">
                          <Typography variant="subheading" color="#606060">
                            {formitem.type_ |> string}
                          </Typography>
                        </GridItem>
                        <GridItem
                          top="6" right="0" bottom="0" left="0" xs="auto">
                          <GridContainer
                            direction="row"
                            justify="center"
                            alignItem="center">
                            <GridItem
                              top="0" right="0" bottom="0" left="0" xs="auto">
                              <Typography variant="subheading" color="#606060">
                                {formitem.address |> string}
                              </Typography>
                            </GridItem>
                            <GridItem
                              top="0" right="0" bottom="0" left="0" xs="no">
                              <Button
                                variant="Link" href={"tel:" ++ formitem.phone}>
                                <FormattedMessage
                                  id="Default.contact"
                                  defaultMessage="Contact"
                                />
                              </Button>
                            </GridItem>
                          </GridContainer>
                        </GridItem>
                        <GridItem
                          top="0" right="0" bottom="0" left="0" xs="auto">
                          <GridContainer
                            direction="columnReverse"
                            justify="center"
                            alignItem="stretch">
                            {formitem.menuitems
                             |> Array.map(menuitem =>
                                  <>
                                    <GridItem
                                      top="6"
                                      right="0"
                                      bottom="6"
                                      left="0"
                                      xs="auto">
                                      <GridContainer
                                        direction="column"
                                        justify="center"
                                        alignItem="stretch">
                                        <GridItem
                                          top="0" right="0" left="0" xs="auto">
                                          <GridContainer
                                            direction="row"
                                            justify="center"
                                            alignItem="center">
                                            <GridItem
                                              top="0"
                                              right="0"
                                              bottom="0"
                                              left="0"
                                              xs="no">
                                              <Typography
                                                variant="subheading"
                                                fontSize="1.2rem"
                                                fontWeight="600">
                                                {menuitem.name |> string}
                                              </Typography>
                                            </GridItem>
                                            <GridItem
                                              top="0"
                                              right="0"
                                              bottom="0"
                                              xs="auto">
                                              <Typography
                                                variant="subheading"
                                                color="rgba(255,0,0,0.8)"
                                                fontWeight="600">
                                                {menuitem.price |> string}
                                              </Typography>
                                            </GridItem>
                                          </GridContainer>
                                        </GridItem>
                                        <GridItem
                                          top="0" right="0" left="0" xs="auto">
                                          <Image
                                            width="auto"
                                            height="200px"
                                            borderRadius="6"
                                            src={
                                              "data:image/jpg;base64,"
                                              ++ menuitem.album
                                            }
                                          />
                                        </GridItem>
                                        <GridItem
                                          top="0"
                                          right="0"
                                          bottom="0"
                                          left="0"
                                          xs="auto">
                                          <Typography variant="subheading">
                                            <div
                                              dangerouslySetInnerHTML={
                                                "__html": menuitem.remark,
                                              }
                                            />
                                          </Typography>
                                        </GridItem>
                                      </GridContainer>
                                    </GridItem>
                                    <GridItem xs="auto">
                                      <Divider />
                                    </GridItem>
                                  </>
                                )
                             |> array}
                          </GridContainer>
                        </GridItem>
                      </>
                    )
                 |> array
               | 1 =>
                 <GridItem top="0" right="0" bottom="0" left="0" xs="auto">
                   <GridContainer
                     direction="columnReverse"
                     justify="center"
                     alignItem="stretch">
                     {state.chatitems
                      |> Array.mapi((i, chatitem) =>
                           <>
                             <div
                               onMouseEnter={_ => i |> mouseChatItem}
                               onMouseLeave={_ => (-1) |> mouseChatItem}>
                               <GridItem
                                 top="6"
                                 right="0"
                                 bottom="6"
                                 left="0"
                                 xs="auto">
                                 <GridContainer
                                   direction="row"
                                   justify="start"
                                   alignItem="start">
                                   <GridItem
                                     top="0"
                                     right="0"
                                     bottom="0"
                                     left="0"
                                     xs="no">
                                     <Avatar
                                       top="5"
                                       bottom="5"
                                       backgroundColor="rgba(255,0,0,0.8)">
                                       <Typography
                                         variant="tile"
                                         color="rgba(255,255,255,1)">
                                         {chatitem.fstName |> string}
                                       </Typography>
                                     </Avatar>
                                   </GridItem>
                                   <GridItem
                                     top="0"
                                     right="0"
                                     bottom="0"
                                     left="0"
                                     xs="auto">
                                     <GridContainer
                                       direction="column"
                                       justify="center"
                                       alignItem="stretch">
                                       <GridItem
                                         top="0"
                                         right="0"
                                         bottom="0"
                                         left="0"
                                         xs="auto">
                                         <GridContainer
                                           direction="row"
                                           justify="start"
                                           alignItem="center">
                                           <GridItem
                                             top="0"
                                             right="0"
                                             bottom="0"
                                             left="0"
                                             xs="no">
                                             <Typography
                                               variant="subheading"
                                               fontWeight="600">
                                               {chatitem.name |> string}
                                             </Typography>
                                           </GridItem>
                                           <GridItem
                                             top="0"
                                             right="0"
                                             bottom="0"
                                             left="6"
                                             xs="auto">
                                             <Typography
                                               variant="subtitle1"
                                               color="#606060">
                                               {chatitem.datetime |> string}
                                             </Typography>
                                           </GridItem>
                                         </GridContainer>
                                       </GridItem>
                                       <GridItem
                                         top="0"
                                         right="0"
                                         bottom="0"
                                         left="3"
                                         xs="auto">
                                         <Typography variant="subheading">
                                           <div
                                             dangerouslySetInnerHTML={
                                               "__html": chatitem.content,
                                             }
                                           />
                                         </Typography>
                                       </GridItem>
                                     </GridContainer>
                                   </GridItem>
                                   {switch (
                                      chatitem.showEnter,
                                      chatitem.itemDelete,
                                    ) {
                                    | (true, true) =>
                                      <GridItem
                                        style={ReactDOMRe.Style.make(
                                          ~position="relative",
                                          (),
                                        )}
                                        top="0"
                                        right="0"
                                        bottom="0"
                                        left="0"
                                        xs="no">
                                        <IconButton
                                          style={ReactDOMRe.Style.make(
                                            ~position="absolute",
                                            ~top="-6px",
                                            ~right="6px",
                                            (),
                                          )}
                                          padding="6"
                                          disabled={state.showProgress}>
                                          <Tooltip
                                            location="left"
                                            backgroundColor="rgba(255,0,0,0.8)">
                                            <FormattedMessage
                                              id="deleted"
                                              defaultMessage="Deleted"
                                            />
                                          </Tooltip>
                                          <IconAction
                                            animation="circle"
                                            src=clearBlack
                                          />
                                        </IconButton>
                                      </GridItem>
                                    | (_, _) => null
                                    }}
                                 </GridContainer>
                               </GridItem>
                             </div>
                             <GridItem right="24" left="24" xs="auto">
                               <Divider />
                             </GridItem>
                           </>
                         )
                      |> array}
                   </GridContainer>
                 </GridItem>
               | _ => null
               }}
            </GridContainer>
          </GridItem>
        </DialogContentText>
      </DialogContent>
      <DialogActions>
        <div
          style={ReactDOMRe.Style.make(
            ~position="fixed",
            ~top="10px",
            ~left="10px",
            (),
          )}>
          <IconButton
            padding="12"
            disabled={state.showProgress}
            onClick=closeAnimationFull>
            <Tooltip location="bottom" backgroundColor="rgba(255,0,0,0.8)">
              <FormattedMessage id="closed" defaultMessage="Closed" />
            </Tooltip>
            <IconAction animation="circle" src=clearBlack />
          </IconButton>
        </div>
      </DialogActions>
    </DialogFull>
    <SnackbarYoutube showYoutube={state.showYoutube} position="bottomLeft">
      ...(<span> {state.youtubeText |> string} </span>, null)
    </SnackbarYoutube>
  </>;
};
