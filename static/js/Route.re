open Setting;
[@react.component]
let make = _ => {
  let url = ReasonReactRouter.useUrl();

  switch (url.path) {
  | ["login"] => <Login />
  | ["forget"] => <Forget />
  | ["code"] => <Code />
  | ["resend"] => <Resend />
  | ["signup"] => <Signup />
  | ["oauth"] => <Oauth />
  | _ =>
    <NewBookBoard
      autoPath={pathObjects(Js_list.length(url.path), url.path, url.hash)}>
      {switch (url.path) {
       | [] => <Home />
       | ["icon"] => <Icon />
       | ["bookmarks"] => <Bookmarks />
       | ["store"] => <Store />
       | ["carte"] => <Carte />
       | ["busdate"] => <Busdate />
       | ["fesdate"] => <Fesdate />
       | _ => <Home />
       }}
    </NewBookBoard>
  };
};
