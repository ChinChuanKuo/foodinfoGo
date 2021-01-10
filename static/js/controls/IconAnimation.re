open Icons;

[@genType]
let topDownRorate = outShow => outShow ? "justTopDown" : "";

[@genType]
let answerIcon = (outValue, showAnswer) =>
  switch (outValue) {
  | "checkbox" => showAnswer ? checkBoxBlack : checkBoxOutlineBlankBlack
  | _ => showAnswer ? radioButtonCheckedBlack : radioButtonUncheckedBlack
  };