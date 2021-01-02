open React;
open ReactIntl;

[@react.component]
let make =
    (
      ~error: bool,
      ~loading: bool,
      ~showYoutube: bool,
      ~youtubeText: string,
      ~disabled: bool,
      ~userid: string,
      ~changeUserid: option(ReactEvent.Form.t => unit)=?,
      ~keydownUserid: option(ReactEvent.Keyboard.t => unit)=?,
      ~password: string,
      ~changePassword: option(ReactEvent.Form.t => unit)=?,
      ~keydownPassword: option(ReactEvent.Keyboard.t => unit)=?,
      ~forgetForm: option(ReactEvent.Mouse.t => unit)=?,
      ~sendForm: option(ReactEvent.Mouse.t => unit)=?,
    ) =>
  <AccountBoard error loading tile="LOGIN" showYoutube youtubeText>
    <GridContainer direction="column" justify="center" alignItem="stretch">
      <GridItem right="0" left="0" xs="auto">
        <TextFieldOutline
          left="0"
          right="0"
          type_="email"
          value=userid
          disabled
          onChange=?changeUserid
          onKeyDown=?keydownUserid>
          <FormattedMessage id="Login.email" defaultMessage="Email" />
        </TextFieldOutline>
      </GridItem>
      <GridItem top="21" right="0" left="0" xs="auto">
        <TextFieldOutline
          left="0"
          right="0"
          type_="password"
          value=password
          disabled
          onChange=?changePassword
          onKeyDown=?keydownPassword>
          <FormattedMessage id="Login.password" defaultMessage="Password" />
        </TextFieldOutline>
      </GridItem>
      <GridItem top="21" right="0" left="0" xs="auto">
        <GridContainer direction="row" justify="between" alignItem="center">
          <GridItem right="0" left="0" xs="no">
            <Button
              variant="button"
              border="contained"
              size="medium"
              disabled
              onClick=?forgetForm>
              <FormattedMessage id="Account.forget" defaultMessage="Forget" />
            </Button>
          </GridItem>
          <GridItem right="0" left="0" xs="no">
            <Button
              variant="button"
              border="contained"
              size="medium"
              disabled
              onClick=?sendForm>
              <FormattedMessage id="Account.send" defaultMessage="Send" />
            </Button>
          </GridItem>
        </GridContainer>
      </GridItem>
    </GridContainer>
  </AccountBoard>;
