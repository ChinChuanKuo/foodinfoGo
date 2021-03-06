// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as Block from "bs-platform/lib/es6/block.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as Setting$BtsCore from "../../../setting/Setting.bs.js";

((require('../../scss/TextField/textFieldArticle.scss')));

function reducer(state, action) {
  if (action.tag) {
    return {
            enter: state.enter,
            down: action[0]
          };
  }
  var enter = action[0];
  return {
          enter: enter,
          down: enter ? state.down : false
        };
}

var initialState = {
  enter: false,
  down: false
};

function sizes(size) {
  if (size !== undefined) {
    return size + "px";
  } else {
    return "100%";
  }
}

function paddingTopBottoms(topBottom) {
  if (topBottom !== undefined) {
    return topBottom + "px";
  } else {
    return "18.5px";
  }
}

function paddingRightLefts(rightLeft) {
  if (rightLeft !== undefined) {
    return rightLeft + "px";
  } else {
    return "14px";
  }
}

function borderWidths(borderWidth) {
  if (borderWidth !== undefined) {
    return borderWidth + "px";
  } else {
    return "2px";
  }
}

function borderStyles(borderStyle) {
  if (borderStyle !== undefined) {
    return borderStyle;
  } else {
    return "solid";
  }
}

function borderRadiuses(borderRadius) {
  if (borderRadius !== undefined) {
    return borderRadius + "px";
  } else {
    return "4px";
  }
}

function disabledBorderColors(disabledBorderColor) {
  if (disabledBorderColor !== undefined) {
    return disabledBorderColor;
  } else {
    return "rgba(0,0,0,0.26)";
  }
}

function otherBorderColors(otherBorderColor) {
  if (otherBorderColor !== undefined) {
    return otherBorderColor;
  } else {
    return "rgba(255,0,0,0.8)";
  }
}

function borderColors(borderColor) {
  if (borderColor !== undefined) {
    return borderColor;
  } else {
    return "rgba(255,0,0,1)";
  }
}

function colors(color) {
  if (color !== undefined) {
    return color;
  } else {
    return "rgba(0,0,0,1)";
  }
}

function pointerEvents(disabled) {
  if (disabled) {
    return "none";
  } else {
    return "initial";
  }
}

function TextFieldArticle(Props) {
  var style = Props.style;
  var width = Props.width;
  var maxHeight = Props.maxHeight;
  var height = Props.height;
  var top = Props.top;
  var right = Props.right;
  var bottom = Props.bottom;
  var left = Props.left;
  var borderWidth = Props.borderWidth;
  var borderStyle = Props.borderStyle;
  var borderRadius = Props.borderRadius;
  var disabledBorderColor = Props.disabledBorderColor;
  var enterBorderColor = Props.enterBorderColor;
  var downBorderColor = Props.downBorderColor;
  var borderColor = Props.borderColor;
  var color = Props.color;
  var textRef = Props.textRef;
  var disabled = Props.disabled;
  var onInput = Props.onInput;
  var onKeyDown = Props.onKeyDown;
  var onBlur = Props.onBlur;
  var onClick = Props.onClick;
  var match = React.useReducer(reducer, initialState);
  var dispatch = match[1];
  var state = match[0];
  var match$1 = Setting$BtsCore.disabledObjects(disabled);
  var match$2 = state.enter;
  var match$3 = state.down;
  var disabled$1 = Setting$BtsCore.disabledObjects(disabled);
  var tmp = {
    ref: Setting$BtsCore.refObjects(textRef),
    className: "j1pa5zxfe j1m8k26r",
    contentEditable: !Setting$BtsCore.disabledObjects(disabled),
    style: Object.assign(({}), {
          borderColor: match$1 ? (
              disabledBorderColor !== undefined ? disabledBorderColor : "rgba(0,0,0,0.26)"
            ) : (
              match$2 ? (
                  match$3 ? (
                      downBorderColor !== undefined ? downBorderColor : "rgba(255,0,0,0.8)"
                    ) : (
                      enterBorderColor !== undefined ? enterBorderColor : "rgba(255,0,0,0.8)"
                    )
                ) : (
                  borderColor !== undefined ? borderColor : "rgba(255,0,0,1)"
                )
            ),
          borderStyle: borderStyle !== undefined ? borderStyle : "solid",
          borderWidth: borderWidths(borderWidth),
          color: color !== undefined ? color : "rgba(0,0,0,1)",
          display: "block",
          height: sizes(height),
          outline: "none",
          overflow: "auto",
          paddingTop: paddingTopBottoms(top),
          paddingRight: paddingRightLefts(right),
          paddingBottom: paddingTopBottoms(bottom),
          paddingLeft: paddingRightLefts(left),
          borderRadius: borderRadiuses(borderRadius),
          pointerEvents: disabled$1 ? "none" : "initial"
        }, Setting$BtsCore.styleObjects(style)),
    onMouseDown: (function (param) {
        return Curry._1(dispatch, /* MouseUpDown */Block.__(1, [true]));
      }),
    onMouseEnter: (function (param) {
        return Curry._1(dispatch, /* MouseEnterLeave */Block.__(0, [true]));
      }),
    onMouseLeave: (function (param) {
        return Curry._1(dispatch, /* MouseEnterLeave */Block.__(0, [false]));
      }),
    onMouseUp: (function (param) {
        return Curry._1(dispatch, /* MouseUpDown */Block.__(1, [false]));
      }),
    suppressContentEditableWarning: !Setting$BtsCore.disabledObjects(disabled)
  };
  if (onKeyDown !== undefined) {
    tmp.onKeyDown = Caml_option.valFromOption(onKeyDown);
  }
  if (onBlur !== undefined) {
    tmp.onBlur = Caml_option.valFromOption(onBlur);
  }
  if (onInput !== undefined) {
    tmp.onInput = Caml_option.valFromOption(onInput);
  }
  if (onClick !== undefined) {
    tmp.onClick = Caml_option.valFromOption(onClick);
  }
  return React.createElement("div", {
              style: {
                maxHeight: sizes(maxHeight),
                width: sizes(width)
              }
            }, React.createElement("div", tmp));
}

var make = TextFieldArticle;

export {
  reducer ,
  initialState ,
  sizes ,
  paddingTopBottoms ,
  paddingRightLefts ,
  borderWidths ,
  borderStyles ,
  borderRadiuses ,
  disabledBorderColors ,
  otherBorderColors ,
  borderColors ,
  colors ,
  pointerEvents ,
  make ,
  
}
/*  Not a pure module */
