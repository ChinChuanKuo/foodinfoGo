module General = {
  [@genType]
  let top = (i, all) =>
    i < 2 ? "0" : i == all - 1 || i == all - 2 ? "auto" : "50%";
  [@genType]
  let bottom = (i, all) => i == all - 1 ? "0" : i == all - 2 ? "50%" : "auto";
  [@genType]
  let transform = (i, all) =>
    i < 2 || i == all - 1
      ? "translate(0, 0)"
      : i == all - 2 ? "translate(0, 50%)" : "translate(0, -50%)";
};
module Filter = {
  [@genType]
  let left = i => i == 0 ? "auto" : "100%";
  [@genType]
  let transform = i => i == 0 ? "translate(-10%, 0)" : "translate(-100%, 0)";
};