open React;
open ReactIntl;
open Setting;
open Icons;
open Items;
open Document;
open IconAnimation;

type sizeitem = {
  disablePadding: bool,
  size: string,
  value: string,
};

type state = {
  showName: bool,
  name: string,
  nameitems: array(optionitem),
  showSize: bool,
  sizeitems: array(sizeitem),
  showAlign: bool,
  showMore: bool,
};

type action =
  | ShowName
  | ClickNameMenu(string)
  | ShowSize
  | ShowAlign
  | ShowMore;

let reducer = (state, action) =>
  switch (action) {
  | ShowName => {...state, showName: !state.showName}
  | ClickNameMenu(value) => {...state, name: value, showName: false}
  | ShowSize => {...state, showSize: !state.showSize}
  | ShowAlign => {...state, showAlign: !state.showAlign}
  | ShowMore => {...state, showMore: !state.showMore}
  };

let initialState = {
  showName: false,
  name: "Sans Serif",
  nameitems: [|
    {optionPadding: false, value: "Microsoft JhengHei"},
    {optionPadding: false, value: "PMingLiU"},
    {optionPadding: false, value: "MingLiU"},
    {optionPadding: false, value: "Sans Serif"},
    {optionPadding: false, value: "Serif"},
    {optionPadding: false, value: "Monospace font"},
    {optionPadding: false, value: "width"},
    {optionPadding: false, value: "narrow"},
    {optionPadding: false, value: "Comic Sans MS"},
    {optionPadding: false, value: "Garamond"},
    {optionPadding: false, value: "Georgia"},
    {optionPadding: false, value: "Tahoma"},
    {optionPadding: false, value: "Trebuchet MS"},
    {optionPadding: false, value: "Verdana"},
  |],
  showSize: false,
  sizeitems: [|
    {disablePadding: false, size: "1", value: "small"},
    {disablePadding: false, size: "3", value: "general"},
    {disablePadding: false, size: "4", value: "larger"},
    {disablePadding: false, size: "6", value: "largest"},
  |],
  showAlign: false,
  showMore: false,
};

[@react.component]
let make = (~disabled: option(bool)=?, ~width: option(int)=?) => {
  let (state, dispatch) = useReducer(reducer, initialState);

  let clickUndo = useCallback(_ => ExecCommands.make("undo", false, ""));
  let clickRedo = useCallback(_ => ExecCommands.make("redo", false, ""));
  let showName = useCallback(_ => ShowName |> dispatch);
  let clickNameMenu =
    useCallback(value => {
      ClickNameMenu(value) |> dispatch;
      ExecCommands.make("fontName", false, value);
    });
  let showSize = useCallback(_ => ShowSize |> dispatch);
  let clickSizeMenu =
    useCallback(size => ExecCommands.make("fontSize", false, size));
  let formatBold = useCallback(_ => ExecCommands.make("bold", false, ""));
  let formatItalic = useCallback(_ => ExecCommands.make("italic", false, ""));
  let underline = useCallback(_ => ExecCommands.make("underline", false, ""));
  let showAlign = useCallback(_ => ShowAlign |> dispatch);
  let alignLeft =
    useCallback(_ => ExecCommands.make("justifyLeft", false, ""));
  let alignCenter =
    useCallback(_ => ExecCommands.make("justifyCenter", false, ""));
  let alignRight =
    useCallback(_ => ExecCommands.make("justifyRight", false, ""));
  let insertorderedlist =
    useCallback(_ => ExecCommands.make("insertorderedlist", false, ""));
  let insertUnorderedlist =
    useCallback(_ => ExecCommands.make("insertUnorderedlist", false, ""));
  let outdent = useCallback(_ => ExecCommands.make("outdent", false, ""));
  let indent = useCallback(_ => ExecCommands.make("indent", false, ""));
  let showMore = useCallback(_ => ShowMore |> dispatch);
  let removeFormat =
    useCallback(_ => ExecCommands.make("removeFormat", false, ""));
  let strikethrough =
    useCallback(_ => ExecCommands.make("strikethrough", false, ""));

  <AppBar
    backgroundColor="rgba(255,255,255,1)" position="relative" zIndex="1" minHeight="40">
    <GridContainer direction="rowReverse" justify="center" alignItem="center">
      <GridItem top="0" right="6" bottom="0" left="0" xs="no">
        <IconButton padding="4" onClick=showMore>
          <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
            <FormattedMessage id="Toolbar.more" defaultMessage="More" />
          </Tooltip>
          <IconAction animation="leftRight" src=arrowDownBlack />
        </IconButton>
        {state.showMore
           ? <>
               <SelectMenu
                 top="50%"
                 transform="translate(0, -50%)"
                 width="auto"
                 maxHeight="280"
                 minHeight="0"
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
                   onClick=removeFormat>
                   <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
                     <FormattedMessage
                       id="Toolbar.remove"
                       defaultMessage="Remove"
                     />
                   </Tooltip>
                   <IconGeneral src=formatClearBlack />
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
                   onClick=strikethrough>
                   <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
                     <FormattedMessage
                       id="Toolbar.strike"
                       defaultMessage="Strike"
                     />
                   </Tooltip>
                   <IconGeneral src=strikethroughSBlack />
                 </MenuItem>
                 {switch (intObjects(width) < 900) {
                  | true =>
                    <MenuItem
                      top="0"
                      right="8"
                      bottom="0"
                      left="8"
                      topLeft="12"
                      topRight="12"
                      bottomRight="12"
                      bottomLeft="12"
                      onClick=indent>
                      <Tooltip
                        location="top" backgroundColor="rgba(255,0,0,0.8)">
                        <FormattedMessage
                          id="Toolbar.increase"
                          defaultMessage="Increase"
                        />
                      </Tooltip>
                      <IconGeneral src=formatIndentIncreaseBlack />
                    </MenuItem>
                  | _ => null
                  }}
                 {switch (intObjects(width) < 850) {
                  | true =>
                    <MenuItem
                      top="0"
                      right="8"
                      bottom="0"
                      left="8"
                      topLeft="12"
                      topRight="12"
                      bottomRight="12"
                      bottomLeft="12"
                      onClick=outdent>
                      <Tooltip
                        location="top" backgroundColor="rgba(255,0,0,0.8)">
                        <FormattedMessage
                          id="Toolbar.decrease"
                          defaultMessage="Decrease"
                        />
                      </Tooltip>
                      <IconGeneral src=formatIndentDecreaseBlack />
                    </MenuItem>
                  | _ => null
                  }}
                 {switch (intObjects(width) < 800) {
                  | true =>
                    <MenuItem
                      top="0"
                      right="8"
                      bottom="0"
                      left="8"
                      topLeft="12"
                      topRight="12"
                      bottomRight="12"
                      bottomLeft="12"
                      onClick=insertUnorderedlist>
                      <Tooltip
                        location="top" backgroundColor="rgba(255,0,0,0.8)">
                        <FormattedMessage
                          id="Toolbar.bullist"
                          defaultMessage="Bullist"
                        />
                      </Tooltip>
                      <IconGeneral src=formatListBulletedBlack />
                    </MenuItem>
                  | _ => null
                  }}
                 {switch (intObjects(width) < 750) {
                  | true =>
                    <MenuItem
                      top="0"
                      right="8"
                      bottom="0"
                      left="8"
                      topLeft="12"
                      topRight="12"
                      bottomRight="12"
                      bottomLeft="12"
                      onClick=insertorderedlist>
                      <Tooltip
                        location="top" backgroundColor="rgba(255,0,0,0.8)">
                        <FormattedMessage
                          id="Toolbar.ordlist"
                          defaultMessage="Ordlist"
                        />
                      </Tooltip>
                      <IconAction
                        animation="leftRight"
                        src=formatListNumberedBlack
                      />
                    </MenuItem>
                  | _ => null
                  }}
               </SelectMenu>
               <BackgroundBoard
                 showBackground={state.showMore}
                 backgroundColor="transparent"
                 onClick=showMore
               />
             </>
           : null}
      </GridItem>
      <GridItem
        style={ReactDOMRe.Style.make(
          ~height="25px",
          ~marginTop="6px",
          ~marginRight="3px",
          ~borderRight="1px solid rgba(0,0,0,0.08)",
          (),
        )}
        top="0"
        right="0"
        bottom="0"
        left="3"
        xs="no">
        null
      </GridItem>
      {switch (intObjects(width) >= 900) {
       | true =>
         <GridItem top="0" right="0" bottom="0" left="0" xs="no">
           <IconButton padding="4" onClick=indent>
             <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
               <FormattedMessage
                 id="Toolbar.increase"
                 defaultMessage="Increase"
               />
             </Tooltip>
             <IconAction animation="leftRight" src=formatIndentIncreaseBlack />
           </IconButton>
         </GridItem>
       | _ => null
       }}
      {switch (intObjects(width) >= 850) {
       | true =>
         <GridItem top="0" right="0" bottom="0" left="0" xs="no">
           <IconButton padding="4" onClick=outdent>
             <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
               <FormattedMessage
                 id="Toolbar.decrease"
                 defaultMessage="Decrease"
               />
             </Tooltip>
             <IconAction animation="leftRight" src=formatIndentDecreaseBlack />
           </IconButton>
         </GridItem>
       | _ => null
       }}
      {switch (intObjects(width) >= 800) {
       | true =>
         <GridItem top="0" right="0" bottom="0" left="0" xs="no">
           <IconButton padding="4" onClick=insertUnorderedlist>
             <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
               <FormattedMessage
                 id="Toolbar.bullist"
                 defaultMessage="Bullist"
               />
             </Tooltip>
             <IconAction animation="leftRight" src=formatListBulletedBlack />
           </IconButton>
         </GridItem>
       | _ => null
       }}
      {switch (intObjects(width) >= 750) {
       | true =>
         <GridItem top="0" right="0" bottom="0" left="0" xs="no">
           <IconButton padding="4" onClick=insertorderedlist>
             <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
               <FormattedMessage
                 id="Toolbar.ordlist"
                 defaultMessage="Ordlist"
               />
             </Tooltip>
             <IconAction animation="leftRight" src=formatListNumberedBlack />
           </IconButton>
         </GridItem>
       | _ => null
       }}
      <GridItem top="0" right="0" bottom="0" left="0" xs="no">
        <IconButton padding="4" onClick=showAlign>
          <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
            <FormattedMessage id="Toolbar.align" defaultMessage="Align" />
          </Tooltip>
          <IconAction animation="leftRight" src=formatAlignRightBlack />
        </IconButton>
        {state.showAlign
           ? <>
               <SelectMenu
                 top="50%"
                 transform="translate(0, -50%)"
                 width="auto"
                 maxHeight="280"
                 minHeight="0"
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
                   onClick=alignLeft>
                   <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
                     <FormattedMessage
                       id="Toolbar.left"
                       defaultMessage="Left"
                     />
                   </Tooltip>
                   <IconGeneral src=formatAlignLeftBlack />
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
                   onClick=alignCenter>
                   <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
                     <FormattedMessage
                       id="Toolbar.center"
                       defaultMessage="Center"
                     />
                   </Tooltip>
                   <IconGeneral src=formatAlignCenterBlack />
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
                   onClick=alignRight>
                   <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
                     <FormattedMessage
                       id="Toolbar.right"
                       defaultMessage="Right"
                     />
                   </Tooltip>
                   <IconGeneral src=formatAlignRightBlack />
                 </MenuItem>
               </SelectMenu>
               <BackgroundBoard
                 showBackground={state.showAlign}
                 backgroundColor="transparent"
                 onClick=showAlign
               />
             </>
           : null}
      </GridItem>
      <GridItem
        style={ReactDOMRe.Style.make(
          ~height="25px",
          ~marginTop="6px",
          ~marginRight="3px",
          ~borderRight="1px solid rgba(0,0,0,0.08)",
          (),
        )}
        top="0"
        right="0"
        bottom="0"
        left="3"
        xs="no">
        null
      </GridItem>
      <GridItem top="0" right="0" bottom="0" left="0" xs="no">
        <IconButton padding="4">
          <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
            <FormattedMessage id="Toolbar.color" defaultMessage="Color" />
          </Tooltip>
          <IconAction animation="leftRight" src=textFormatBlack />
        </IconButton>
      </GridItem>
      <GridItem top="0" right="0" bottom="0" left="0" xs="no">
        <IconButton padding="4" onClick=underline>
          <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
            <FormattedMessage
              id="Toolbar.underline"
              defaultMessage="Underline"
            />
          </Tooltip>
          <IconAction animation="leftRight" src=formatUnderlinedBlack />
        </IconButton>
      </GridItem>
      <GridItem top="0" right="0" bottom="0" left="0" xs="no">
        <IconButton padding="4" onClick=formatItalic>
          <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
            <FormattedMessage id="Toolbar.italic" defaultMessage="Italic" />
          </Tooltip>
          <IconAction animation="leftRight" src=formatItalicBlack />
        </IconButton>
      </GridItem>
      <GridItem top="0" right="0" bottom="0" left="0" xs="no">
        <IconButton padding="4" onClick=formatBold>
          <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
            <FormattedMessage id="Toolbar.bold" defaultMessage="Bold" />
          </Tooltip>
          <IconAction animation="leftRight" src=formatBoldBlack />
        </IconButton>
      </GridItem>
      <GridItem
        style={ReactDOMRe.Style.make(
          ~height="25px",
          ~marginTop="6px",
          ~marginRight="3px",
          ~borderRight="1px solid rgba(0,0,0,0.08)",
          (),
        )}
        top="0"
        right="0"
        bottom="0"
        left="3"
        xs="no">
        null
      </GridItem>
      <GridItem top="0" right="0" bottom="0" left="6" xs="no">
        <IconButton padding="4" onClick=showSize>
          <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
            <FormattedMessage id="Toolbar.size" defaultMessage="Size" />
          </Tooltip>
          <IconAction animation="leftRight" src=formatSizeBlack />
        </IconButton>
        {state.showSize
           ? <>
               <SelectMenu
                 top="50%"
                 transform="translate(0, -50%)"
                 width="105"
                 maxHeight="280"
                 minHeight="0"
                 topLeft="12"
                 topRight="12"
                 bottomRight="12"
                 bottomLeft="12"
                 paddingRight="8"
                 paddingLeft="8">
                 {state.sizeitems
                  |> Array.map(sizeitem =>
                       <MenuItem
                         top="0"
                         right="8"
                         bottom="0"
                         left="8"
                         disablePadding={sizeitem.disablePadding}
                         topLeft="12"
                         topRight="12"
                         bottomRight="12"
                         bottomLeft="12"
                         onClick={_ => sizeitem.size |> clickSizeMenu}>
                         {sizeitem.value |> string}
                       </MenuItem>
                     )
                  |> array}
               </SelectMenu>
               <BackgroundBoard
                 showBackground={state.showSize}
                 backgroundColor="transparent"
                 onClick=showSize
               />
             </>
           : null}
      </GridItem>
      <GridItem
        style={ReactDOMRe.Style.make(~minWidth="135px", ())}
        top="0"
        right="0"
        bottom="0"
        left="6"
        xs="auto">
        <SelectStandard
          top="0"
          right="0"
          bottom="0"
          left="0"
          borderTop="6"
          borderBottom="6"
          borderWidth="0"
          enterBorderColor="rgba(255,0,0,0.8)"
          downBorderColor="rgba(255,0,0,0.6)"
          borderColor="rgba(0,0,0,0.2)"
          value={state.name}
          disabled={disabled |> disabledObjects}
          onClick=showName>
          ...(
               state.showName
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
                     {state.nameitems
                      |> Array.map(nameitem =>
                           <MenuItem
                             top="0"
                             right="8"
                             bottom="0"
                             left="8"
                             disablePadding={nameitem.optionPadding}
                             topLeft="12"
                             topRight="12"
                             bottomRight="12"
                             bottomLeft="12"
                             onClick={_ => nameitem.value |> clickNameMenu}>
                             {nameitem.value |> string}
                           </MenuItem>
                         )
                      |> array}
                   </SelectMenu>
                 : null,
               <IconGeneral
                 animation={state.showName |> topDownRorate}
                 src=arrowDownBlack
               />,
             )
        </SelectStandard>
        <BackgroundBoard
          showBackground={state.showName}
          backgroundColor="transparent"
          onClick=showName
        />
      </GridItem>
      <GridItem top="0" right="0" bottom="0" left="6" xs="no">
        <IconButton padding="4" onClick=clickRedo>
          <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
            <FormattedMessage id="Toolbar.redo" defaultMessage="Redo" />
          </Tooltip>
          <IconAction animation="leftRight" src=redoBlack />
        </IconButton>
      </GridItem>
      <GridItem top="0" right="0" bottom="0" left="6" xs="no">
        <IconButton padding="4" onClick=clickUndo>
          <Tooltip location="top" backgroundColor="rgba(255,0,0,0.8)">
            <FormattedMessage id="Toolbar.undo" defaultMessage="Undo" />
          </Tooltip>
          <IconAction animation="leftRight" src=undoBlack />
        </IconButton>
      </GridItem>
    </GridContainer>
  </AppBar>;
};
