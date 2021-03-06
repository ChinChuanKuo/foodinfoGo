// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as Block from "bs-platform/lib/es6/block.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as Setting$BtsCore from "../../../setting/Setting.bs.js";

((require('../../scss/TextField/textFieldOutline.scss')));

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

function widths(width) {
  if (width !== undefined) {
    return "calc(" + (width + "% - 12px)");
  } else {
    return "calc(100% - 12px)";
  }
}

function marginTops(top) {
  if (top !== undefined) {
    return top + "px";
  } else {
    return "16px";
  }
}

function marginOthers(other) {
  if (other !== undefined) {
    return other + "px";
  } else {
    return "8px";
  }
}

function disabledColors(disabledBorderColor) {
  if (disabledBorderColor !== undefined) {
    return disabledBorderColor;
  } else {
    return "rgba(0,0,0,0.26)";
  }
}

function colors(color) {
  if (color !== undefined) {
    return color;
  } else {
    return "rgba(255,0,0,0.6)";
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

function fontColors(fontColor) {
  if (fontColor !== undefined) {
    return fontColor;
  } else {
    return "rgba(0,0,0,1)";
  }
}

function types(type_) {
  if (type_ !== undefined) {
    return type_;
  } else {
    return "text";
  }
}

function placeholders(placeholder) {
  if (placeholder !== undefined) {
    return placeholder;
  } else {
    return "Please enter";
  }
}

function TextFieldOutline(Props) {
  var width = Props.width;
  var top = Props.top;
  var right = Props.right;
  var bottom = Props.bottom;
  var left = Props.left;
  var disabledLabelColor = Props.disabledLabelColor;
  var labelColor = Props.labelColor;
  var style = Props.style;
  var borderTop = Props.borderTop;
  var borderRight = Props.borderRight;
  var borderBottom = Props.borderBottom;
  var borderLeft = Props.borderLeft;
  var borderWidth = Props.borderWidth;
  var borderStyle = Props.borderStyle;
  var borderRadius = Props.borderRadius;
  var disabledBorderColor = Props.disabledBorderColor;
  var enterBorderColor = Props.enterBorderColor;
  var downBorderColor = Props.downBorderColor;
  var borderColor = Props.borderColor;
  var fontColor = Props.fontColor;
  var type_ = Props.type_;
  var placeholder = Props.placeholder;
  var value = Props.value;
  var disabled = Props.disabled;
  var onChange = Props.onChange;
  var onKeyDown = Props.onKeyDown;
  var onBlur = Props.onBlur;
  var onClick = Props.onClick;
  var children = Props.children;
  var match = React.useReducer(reducer, initialState);
  var dispatch = match[1];
  var state = match[0];
  var match$1 = Setting$BtsCore.disabledObjects(disabled);
  var match$2 = state.enter;
  var match$3 = state.down;
  var tmp = {
    className: "j4ap7vg j106nmqb",
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
          color: fontColor !== undefined ? fontColor : "rgba(0,0,0,1)",
          paddingTop: paddingTopBottoms(borderTop),
          paddingRight: paddingRightLefts(borderRight),
          paddingBottom: paddingTopBottoms(borderBottom),
          paddingLeft: paddingRightLefts(borderLeft),
          borderRadius: borderRadiuses(borderRadius)
        }, Setting$BtsCore.styleObjects(style)),
    disabled: Setting$BtsCore.disabledObjects(disabled),
    placeholder: placeholder !== undefined ? placeholder : "Please enter",
    type: type_ !== undefined ? type_ : "text",
    value: Setting$BtsCore.stringObjects(value),
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
      })
  };
  if (onKeyDown !== undefined) {
    tmp.onKeyDown = Caml_option.valFromOption(onKeyDown);
  }
  if (onBlur !== undefined) {
    tmp.onBlur = Caml_option.valFromOption(onBlur);
  }
  if (onChange !== undefined) {
    tmp.onChange = Caml_option.valFromOption(onChange);
  }
  if (onClick !== undefined) {
    tmp.onClick = Caml_option.valFromOption(onClick);
  }
  return React.createElement("div", {
              className: "joig26a",
              style: {
                marginTop: marginTops(top),
                marginRight: marginOthers(right),
                marginBottom: marginOthers(bottom),
                marginLeft: marginOthers(left),
                width: widths(width)
              }
            }, React.createElement("label", {
                  className: "j1g19fqe j189b1ed j12la19 j1sj1d1q j1azw8op",
                  style: {
                    backgroundColor: "rgba(255,255,255,1)",
                    color: Setting$BtsCore.disabledObjects(disabled) ? (
                        disabledLabelColor !== undefined ? disabledLabelColor : "rgba(0,0,0,0.26)"
                      ) : (
                        labelColor !== undefined ? labelColor : "rgba(255,0,0,0.6)"
                      ),
                    paddingRight: "5px",
                    paddingLeft: "5px"
                  }
                }, children), React.createElement("div", {
                  className: "jbr6nlo j7v6wc2"
                }, React.createElement("input", tmp)));
}

var make = TextFieldOutline;

export {
  reducer ,
  initialState ,
  widths ,
  marginTops ,
  marginOthers ,
  disabledColors ,
  colors ,
  paddingTopBottoms ,
  paddingRightLefts ,
  borderWidths ,
  borderStyles ,
  borderRadiuses ,
  otherBorderColors ,
  borderColors ,
  fontColors ,
  types ,
  placeholders ,
  make ,
  
}
/*  Not a pure module */
