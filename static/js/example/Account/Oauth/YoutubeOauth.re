open ReactIntl;

[@react.component]
let make =
    (
      ~error: bool,
      ~loading: bool,
      ~showYoutube: bool,
      ~youtubeText: string,
      ~disabled: bool,
      ~signGoogle: option(ReactEvent.Mouse.t => unit)=?,
      ~signFacebook: option(ReactEvent.Mouse.t => unit)=?,
      ~signLinkedln: option(ReactEvent.Mouse.t => unit)=?,
      ~signTwitter: option(ReactEvent.Mouse.t => unit)=?,
    ) =>
  <AccountBoard error loading index=2 tile="OAUTH" showYoutube youtubeText>
    <GridContainer direction="column" justify="center" alignItem="stretch">
      <GridItem right="0" left="0" xs="auto">
        <Button
          variant="button"
          width="100%"
          border="contained"
          size="medium"
          disabled
          onClick=?signGoogle>
          <FormattedMessage id="Oauth.google" defaultMessage="Google" />
        </Button>
      </GridItem>
      <GridItem right="0" left="0" xs="auto">
        <Button
          variant="button"
          enterBackgroundColor="rgba(45,136,255,0.8)"
          downBackgroundColor="rgba(45,136,255,0.8)"
          backgroundColor="rgba(45,136,255,1)"
          width="100%"
          border="contained"
          size="medium"
          disabled
          onClick=?signFacebook>
          <FormattedMessage id="Oauth.facebook" defaultMessage="Facebook" />
        </Button>
      </GridItem>
      <GridItem right="0" left="0" xs="auto">
        <Button
          variant="button"
          enterBackgroundColor="rgba(0,119,181,0.8)"
          downBackgroundColor="rgba(0,119,181,0.8)"
          backgroundColor="rgba(0,119,181,1)"
          width="100%"
          border="contained"
          size="medium"
          disabled
          onClick=?signLinkedln>
          <FormattedMessage id="Oauth.linkedln" defaultMessage="Linkedln" />
        </Button>
      </GridItem>
      <GridItem right="0" left="0" xs="auto">
        <Button
          variant="button"
          enterBackgroundColor="rgba(21,32,43,0.8)"
          downBackgroundColor="rgba(21,32,43,0.8)"
          backgroundColor="rgba(21,32,43,1)"
          width="100%"
          border="contained"
          size="medium"
          disabled
          onClick=?signTwitter>
          <FormattedMessage id="Oauth.twitter" defaultMessage="Twitter" />
        </Button>
      </GridItem>
    </GridContainer>
  </AccountBoard>;
