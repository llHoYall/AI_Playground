const fs = require("fs");
const path = require("path");

const csv = fs.readFileSync(
  path.join(__dirname, "database", "images.csv"),
  "utf-8"
);
const all = csv.split("\n");
const shuffle = () => Math.random() - 0.5;
const shuffled = all.sort(shuffle);

const train = shuffled.slice(0, 2000);
const test = shuffled.slice(2000, 2500);

trainFileName = path.join(__dirname, "database", "image-train.csv");
testFileName = path.join(__dirname, "database", "image-test.csv");
fs.writeFileSync(trainFileName, train.join("\n"));
fs.writeFileSync(testFileName, test.join("\n"));
console.log("OK");
