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
      ~code: string,
      ~changeCode: option(ReactEvent.Form.t => unit)=?,
      ~keydownCode: option(ReactEvent.Keyboard.t => unit)=?,
      ~backForm: option(ReactEvent.Mouse.t => unit)=?,
      ~nextForm: option(ReactEvent.Mouse.t => unit)=?,
    ) =>
  <AccountBoard error loading index=3 tile="CODE" showYoutube youtubeText>
    <GridContainer direction="column" justify="center" alignItem="stretch">
      <GridItem right="0" left="0" xs="auto">
        <TextFieldOutline
          left="0"
          right="0"
          value=code
          disabled
          onChange=?changeCode
          onKeyDown=?keydownCode>
          <FormattedMessage
            id="Code.verification"
            defaultMessage="Verification"
          />
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
