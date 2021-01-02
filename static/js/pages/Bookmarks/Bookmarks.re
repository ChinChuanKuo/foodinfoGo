open React;
open ReactIntl;
open Data;
open Icons;
open Axiosapi;
open Storage;
open ObjectFormat;

[@react.component]
let make = _ => {
  let storeAJax = () =>
    Js.Promise.(
      "newid"
      |> Locals.select
      |> userData
      |> Default.store
      |> then_(response =>
           {
             switch (response##data##status) {
             | "istrue" =>
               Path.storePath
               ++ "#"
               ++
               response##data##formId
               |> ReasonReactRouter.push
             | _ => response##data##status |> Js.log
             };
           }
           |> resolve
         )
      |> catch(error => error |> Js.log |> resolve)
      |> ignore
    );

  let storeForm = useCallback(_ => storeAJax());

  <Drawer
    style={ReactDOMRe.Style.make(
      ~overflow="hidden",
      ~whiteSpace="nowrap",
      ~borderRight="0",
      ~transition="width 225ms cubic-bezier(0.4, 0, 0.6, 1) 0ms",
      (),
    )}
    top="60"
    left="0"
    width="100vw"
    height="64"
    location="left"
    zIndex="1000">
    <List_ top="16">
      <ListIcon
        style={ReactDOMRe.Style.make(~height="52px", ())}
        enterBackgroundColor="rgba(0,0,0,0.12)"
        downBackgroundColor="rgba(0,0,0,0.06)"
        topLeft="20"
        topRight="20"
        bottomRight="20"
        bottomLeft="20"
        right="0"
        left="0"
        onClick=storeForm>
        ...(
             <Avatar
               top="0"
               right="0"
               bottom="0"
               left="0"
               color="#909090"
               backgroundColor="rgba(0,0,0,0.08)">
               {"name" |> Locals.select |> checkObjects |> string}
             </Avatar>,
             <Typography variant="subheading">
               {"allname" |> Locals.select |> checkObjects |> string}
             </Typography>,
           )
      </ListIcon>
      <ListIcon
        style={ReactDOMRe.Style.make(~height="52px", ())}
        enterBackgroundColor="rgba(0,0,0,0.12)"
        downBackgroundColor="rgba(0,0,0,0.06)"
        topLeft="20"
        topRight="20"
        bottomRight="20"
        bottomLeft="20"
        right="0"
        left="0"
        onClick={_ => Path.homePath |> ReasonReactRouter.push}>
        ...(
             <IconButton backgroundColor="rgba(0,0,0,0.08)">
               <IconGeneral src=homeBlack />
             </IconButton>,
             <Typography variant="subheading">
               <FormattedMessage id="Path.home" defaultMessage="Home" />
             </Typography>,
           )
      </ListIcon>
      <ListIcon
        style={ReactDOMRe.Style.make(~height="52px", ())}
        enterBackgroundColor="rgba(0,0,0,0.12)"
        downBackgroundColor="rgba(0,0,0,0.06)"
        topLeft="20"
        topRight="20"
        bottomRight="20"
        bottomLeft="20"
        right="0"
        left="0"
        onClick={_ => Path.homePath |> ReasonReactRouter.push}>
        ...(
             <IconButton backgroundColor="rgba(0,0,0,0.08)">
               <IconGeneral src=homeBlack />
             </IconButton>,
             <Typography variant="subheading">
               <FormattedMessage id="Path.home" defaultMessage="Home" />
             </Typography>,
           )
      </ListIcon>
    </List_>
  </Drawer>;
};
