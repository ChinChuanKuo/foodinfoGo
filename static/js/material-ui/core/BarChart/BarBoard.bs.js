// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as React from "react";
import * as Setting$BtsCore from "../../../setting/Setting.bs.js";

function widths(width) {
  if (width !== undefined) {
    return width;
  } else {
    return "650";
  }
}

function heights(size) {
  if (size !== undefined) {
    return size;
  } else {
    return "500";
  }
}

function transforms(transform) {
  if (transform !== undefined) {
    return "rotate(" + (transform + "deg)");
  } else {
    return "rotate(0deg)";
  }
}

function backgroundColors(backgroundColor) {
  if (backgroundColor !== undefined) {
    return backgroundColor;
  } else {
    return "transparent";
  }
}

function BarBoard(Props) {
  var style = Props.style;
  var width = Props.width;
  var height = Props.height;
  var transform = Props.transform;
  var backgroundColor = Props.backgroundColor;
  var children = Props.children;
  return React.createElement("svg", {
              style: Object.assign(({}), {
                    backgroundColor: backgroundColor !== undefined ? backgroundColor : "transparent",
                    height: height !== undefined ? height : "500",
                    width: width !== undefined ? width : "650",
                    transform: transforms(transform)
                  }, Setting$BtsCore.styleObjects(style))
            }, children);
}

var make = BarBoard;

export {
  widths ,
  heights ,
  transforms ,
  backgroundColors ,
  make ,
  
}
/* react Not a pure module */
