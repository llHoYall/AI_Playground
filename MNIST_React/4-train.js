const fs = require("fs");
const path = require("path");
const svm = require("node-svm");

const data = loadCSV("./database/image-train.csv");

const clf = new svm.CSVC();
clf
  .train(data)
  .progress(progress => {
    console.log("Train: %d%", Math.round(progress * 100));
  })
  .spread((model, report) => {
    const json = JSON.stringify(model);
    fs.writeFileSync(path.join(__dirname, "database", "image-model.svm"), json);
    console.log("Complete");
  });

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
