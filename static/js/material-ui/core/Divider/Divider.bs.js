// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as React from "react";
import * as Setting$BtsCore from "../../../setting/Setting.bs.js";

((require('../../scss/Divider/divider.scss')));

function margins(margin) {
  if (margin !== undefined) {
    return margin + "px";
  } else {
    return "0px";
  }
}

function heights(height) {
  if (height !== undefined) {
    return height + "px";
  } else {
    return "1px";
  }
}

function backgroundColors(backgroundColor) {
  if (backgroundColor !== undefined) {
    return backgroundColor;
  } else {
    return "rgba(0,0,0,0.12)";
  }
}

function Divider(Props) {
  var style = Props.style;
  var top = Props.top;
  var right = Props.right;
  var bottom = Props.bottom;
  var left = Props.left;
  var height = Props.height;
  var backgroundColor = Props.backgroundColor;
  return React.createElement("hr", {
              className: "j1c9j684",
              style: Object.assign(({}), {
                    backgroundColor: backgroundColor !== undefined ? backgroundColor : "rgba(0,0,0,0.12)",
                    height: heights(height),
                    marginTop: margins(top),
                    marginRight: margins(right),
                    marginBottom: margins(bottom),
                    marginLeft: margins(left)
                  }, Setting$BtsCore.styleObjects(style))
            });
}

var make = Divider;

export {
  margins ,
  heights ,
  backgroundColors ,
  make ,
  
}
/*  Not a pure module */