open Revery;
open Revery.UI;
open Revery.UI.Components;


let bgColor = Color.hex("#212733");
let activeBackgroundColor = Color.hex("#2E3440");
let inactiveBackgroundColor = Color.hex("#272d39");
let selectionHighlight = Color.hex("#90f7ff");

module Styles = {
  open Style;
  let text = [marginTop(24), color(Color.hex(Theme.darkBlue))];
  let outerBox = Style.[width(200), height(200), backgroundColor(Colors.black)];
};


let%component main = () => {
  let%hook (count, setCount) = React.Hooks.state(0);
  let%hook (selected: char, setSelected) = React.Hooks.state('a');

   let aview = {
    let increment = () => setCount(count => count + 1);

    <View
    style=Style.[
      position(`Absolute),
      top(0),
      left(300),
      right(0),
      bottom(0)
    ]>
    <Center>
      <Padding padding=24>
        <Row>
          <AnimatedText delay={Time.ms(0)} text="Welcome" />
          <AnimatedText delay={Time.ms(500)} text="to" />
          <AnimatedText delay={Time.ms(1000)} text="A PROGRAM!" />
        </Row>
      </Padding>
      <SimpleButton text="Increment" onClick=increment />
      <Text
        fontSize=16.
        style=Styles.text
        text={"Times clicked: " ++ string_of_int(count)}
      />
     <Row>
     <HackerNews name="hello" />
     </Row>
    </Center>
    </View>;
  };

  let renderButton = letter => {
    let isActive = letter == selected
    let onClick = () => {
      setSelected(selected => letter);
    };
    <View>
    <ExampleButton isActive name={String.make(1, letter)} onClick/>
    </View>
  };

  let bview = {
    <ScrollView
    style=Style.[
          position(`Absolute),
          top(0),
          left(0),
          width(300),
          bottom(0),
          backgroundColor(bgColor),
    ]>
    {List.map(renderButton, ['a', 'b', 'c', 'd', 'e', 'f', 'g']) |> React.listToElement}
    </ScrollView>;
  };


  // overall window
  <View
    style=Style.[
      position(`Absolute),
      alignItems(`Center),
      flexDirection(`Row),
      bottom(0),
      top(0),
      left(0),
      right(0)
    ]>
  bview
  aview
  </View>;
};

let consoleReporter = Timber.Reporter.console(~enableColors=true, ());
let init = app => {
  Revery.App.initConsole();

  Timber.App.enable(consoleReporter);
  Timber.App.setLevel(Timber.Level.perf);

  let win =
    App.createWindow(
      app,
      "Hello Revery!",
      ~createOptions=
        WindowCreateOptions.create(
          ~backgroundColor=Color.hex(Theme.lightBlue),
          ~width=512,
          ~height=384,
          (),
        ),
    );

    Window.setZoom(win, 2.0);

  let _update: Revery.UI.renderFunction = UI.start(win, <main />);
  ();
};

App.start(init);
