// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as $$Array from "bs-platform/lib/es6/array.js";
import * as React from "react";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as TableRow$BtsCore from "../../material-ui/core/Table/TableRow.bs.js";
import * as TableBody$BtsCore from "../../material-ui/core/Table/TableBody.bs.js";
import * as TableCell$BtsCore from "../../material-ui/core/Table/TableCell.bs.js";
import * as TableHead$BtsCore from "../../material-ui/core/Table/TableHead.bs.js";

function Tables(Props) {
  var heads = Props.heads;
  var onClick = Props.onClick;
  var children = Props.children;
  var tmp = {
    children: $$Array.map((function (head) {
            return React.createElement(TableCell$BtsCore.make, {
                        children: head
                      });
          }), heads)
  };
  if (onClick !== undefined) {
    tmp.onClick = Caml_option.valFromOption(onClick);
  }
  return React.createElement(React.Fragment, undefined, React.createElement(TableHead$BtsCore.make, {
                  children: React.createElement(TableRow$BtsCore.make, tmp)
                }), React.createElement(TableBody$BtsCore.make, {
                  children: children
                }));
}

var make = Tables;

export {
  make ,
  
}
/* react Not a pure module */