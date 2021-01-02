// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as $$Array from "bs-platform/lib/es6/array.js";
import * as React from "react";
import * as Caml_array from "bs-platform/lib/es6/caml_array.js";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";

function styleObjects(style) {
  if (style !== undefined) {
    return Caml_option.valFromOption(style);
  } else {
    return { };
  }
}

function disabledObjects(disabled) {
  if (disabled !== undefined) {
    return disabled;
  } else {
    return false;
  }
}

function stringObjects(value) {
  if (value !== undefined) {
    return value;
  } else {
    return "";
  }
}

function floatObjects(value) {
  if (value !== undefined) {
    return value;
  } else {
    return 0.0;
  }
}

function intObjects(value) {
  if (value !== undefined) {
    return value;
  } else {
    return 0;
  }
}

function arrayObjects($$default) {
  if ($$default !== undefined) {
    return $$default;
  } else {
    return [];
  }
}

function refObjects(refs) {
  if (refs !== undefined) {
    return refs;
  } else {
    return React.useRef(null);
  }
}

function pathObjects(count, $$default, hash) {
  if (count !== 0) {
    if (hash === "") {
      return Caml_array.caml_array_get($$Array.of_list($$default), 0);
    } else {
      return Caml_array.caml_array_get($$Array.of_list($$default), 0) + ("#" + hash);
    }
  } else {
    return "/";
  }
}

export {
  styleObjects ,
  disabledObjects ,
  stringObjects ,
  floatObjects ,
  intObjects ,
  arrayObjects ,
  refObjects ,
  pathObjects ,
  
}
/* react Not a pure module */