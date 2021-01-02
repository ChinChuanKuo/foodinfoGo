open React;
open Setting;
open OutSide;
open Together;
open ReactIntl;
open Icons;
[%bs.raw {|require('../../../scss/example/Facebook/newFacetube.scss')|}];

type state = {
  formLoad: bool,
  formWidth: int,
  formHeight: int,
};

type action =
  | SettingFormLoad
  | SettingFormWidth(int, int);

let reducer = (state, action) =>
  switch (action) {
  | SettingFormLoad => {...state, formLoad: !state.formLoad}
  | SettingFormWidth(width, height) => {
      ...state,
      formWidth: width,
      formHeight: height,
    }
  };

let initialState = {formLoad: false, formWidth: 0, formHeight: 0};

let widths = width =>
  switch (width) {
  | None => "95%"
  | Some(width) => width ++ "%"
  };

let bottoms = bottom =>
  switch (bottom) {
  | None => "0px"
  | Some(bottom) => bottom ++ "px"
  };

[@react.component]
let make =
    (
      ~showProgress: option(bool)=?,
      ~error: option(bool)=?,
      ~width: option(string)=?,
      ~bottom: option(string)=?,
      ~children,
    ) => {
  let (state, dispatch) = useReducer(reducer, initialState);
  useEffect(() =>
    if (state.formLoad) {
      Some(() => "action" |> Js.log);
    } else {
      let testId = SettingFormLoad |> dispatch;
      let formId =
        SettingFormWidth(Window.Sizes.width, Window.Sizes.height) |> dispatch;
      Some(
        () => {
          testId;
          formId;
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
    let testId = Window.Listeners.add("resize", handleResize, true) |> ignore;
    Some(() => testId);
  });
  <>
    {showProgress |> disabledObjects
       ? <ProgressLinear style=progressFixed /> : null}
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
      width={state.formWidth < 1100 ? "0px" : "320px"}
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
          onClick={_ => Path.homePath |> ReasonReactRouter.push}>
          ...(
               <IconGeneral src=homeBlack />,
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
          onClick={_ => Path.homePath |> ReasonReactRouter.push}>
          ...(
               <IconGeneral src=homeBlack />,
               <Typography variant="subheading">
                 <FormattedMessage id="Path.home" defaultMessage="Home" />
               </Typography>,
             )
        </ListIcon>
      </List_>
    </Drawer>
    <main
      style={ReactDOMRe.Style.combine(
        mainTube,
        ReactDOMRe.Style.make(
          ~top="80px",
          ~transition=
            "left 225ms cubic-bezier(0.4, 0, 0.6, 1) 0ms, right 225ms cubic-bezier(0.4, 0, 0.6, 1) 0ms",
          ~bottom={
            bottom |> bottoms;
          },
          (),
        ),
      )}
      className="ftmainlayout">
      <div style=divScrollbar>
        <div
          style={ReactDOMRe.Style.combine(
            marginAuto,
            ReactDOMRe.Style.make(
              ~width={
                width |> widths;
              },
              ~maxWidth={
                width |> widths;
              },
              ~flexBasis={
                width |> widths;
              },
              (),
            ),
          )}>
          {error |> disabledObjects
             ? <div style=errorForm>
                 <Typography
                   variant="tile"
                   color="rgba(255,0,0,0.8)"
                   fontSize="x-large">
                   {"UNDEFINED THIS PAGE" |> string}
                 </Typography>
               </div>
             : children}
        </div>
      </div>
    </main>
  </>;
};