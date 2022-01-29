open Revery;
open Revery.UI;
open Revery.UI.Components;

open Lwt;
open Cohttp_lwt_unix;
open Cohttp;

let bgColor = Color.hex("#212733");
let selectionHighlight = Color.hex("#90f7ff");
let activeBackgroundColor = Color.hex("#2E3440");
let inactiveBackgroundColor = Color.hex("#272d39");
let selectionHighlight = Color.hex("#90f7ff");

module Styles = {
  open Style;
  let text = [marginTop(24), color(Color.hex(Theme.darkBlue))];
  let outerBox = Style.[width(200), height(200), backgroundColor(Colors.black)];
};

let print_rq = (uri, meth, hdrs, body) => {
  Printf.sprintf(
    "Uri: %s\nMethod: %s\nHeaders: %s\nBody: %s\n",
    uri,
    meth,
    hdrs,
    body
  );
};

let fetch = () => {
  Client.get(Uri.of_string("http://example.com")) >>= ((resp, body)) => {
    Cohttp_lwt.Body.to_string(body) >|= (body => {
      print_endline(body);
      body;
    }
    )
  };
};

module HackerNews = {
    let textColor = Colors.grey;
    let textHeaderStyle = Style.[color(textColor), margin(16)];
    // let%lwt src = fetch ();
    let wrapperStyle =
      Style.[
        borderLeft(~width=4, ~color=Colors.transparentWhite),
        backgroundColor(bgColor),
      ];

    let onClick () = ();

  
    let%component make = (~name: string, ()) => {
    <Opacity opacity=1.0>
      <Clickable style=wrapperStyle onClick>
        <Text style=textHeaderStyle text=name />
      </Clickable>
    </Opacity>;
    };
};