const fs = require("fs");
const path = require("path");
const svm = require("node-svm");

const json = fs.readFileSync(
  path.join(__dirname, "database", "image-model.svm"),
  "utf-8"
);
const model = JSON.parse(json);
const clf = svm.restore(model);

const testData = loadCSV("./database/image-test.csv");
let count = 0;
let fail = 0;
testData.forEach(element => {
  const x = element[0];
  const label = element[1];
  const predict = clf.predictSync(x);
  if (label !== predict) {
    ++fail;
    console.log("Fail =", label, predict);
  }
  ++count;
});
console.log("Fail Rate =", (fail / count) * 100);

function loadCSV(fname) {
  const csv = fs.readFileSync(fname, "utf-8");
  const lines = csv.split("\n");
  const data = lines.map(line => {
    const cells = line.split(",");
    const x = cells.map(v => parseInt(v));
    const label = x.shift();
    return [x, label];
  });
  return data;
}
