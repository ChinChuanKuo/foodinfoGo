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
      ~fstPassword: string,
      ~changeFstPassword: option(ReactEvent.Form.t => unit)=?,
      ~keydownFstPassword: option(ReactEvent.Keyboard.t => unit)=?,
      ~sndPassword: string,
      ~changeSndPassword: option(ReactEvent.Form.t => unit)=?,
      ~keydownSndPassword: option(ReactEvent.Keyboard.t => unit)=?,
      ~backForm: option(ReactEvent.Mouse.t => unit)=?,
      ~nextForm: option(ReactEvent.Mouse.t => unit)=?,
    ) =>
  <AccountBoard error loading index=3 tile="RESEND" showYoutube youtubeText>
    <GridContainer direction="column" justify="center" alignItem="stretch">
      <GridItem right="0" left="0" xs="auto">
        <TextFieldOutline
          left="0"
          right="0"
          type_="password"
          value=fstPassword
          disabled
          onChange=?changeFstPassword
          onKeyDown=?keydownFstPassword>
          <FormattedMessage id="Resend.first" defaultMessage="First" />
        </TextFieldOutline>
      </GridItem>
      <GridItem top="21" right="0" left="0" xs="auto">
        <TextFieldOutline
          left="0"
          right="0"
          type_="password"
          value=sndPassword
          disabled
          onChange=?changeSndPassword
          onKeyDown=?keydownSndPassword>
          <FormattedMessage id="Resend.second" defaultMessage="Second" />
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
              onClick=?backForm>
              <FormattedMessage id="Account.back" defaultMessage="Back" />
            </Button>
          </GridItem>
          <GridItem right="0" left="0" xs="no">
            <Button
              variant="button"
              border="contained"
              size="medium"
              disabled
              onClick=?nextForm>
              <FormattedMessage id="Account.send" defaultMessage="Send" />
            </Button>
          </GridItem>
        </GridContainer>
      </GridItem>
    </GridContainer>
  </AccountBoard>;
