const path = require("path");
const fs = require("fs");
const express = require("express");
const svm = require("node-svm");

const SVM_MODEL = path.join(__dirname, "database", "image-model.svm");
const portNo = 3002;

const app = express();
app.listen(portNo, () => {
  console.log("Server on:", `http://localhost:${portNo}`);
});

const modelJSON = fs.readFileSync(SVM_MODEL, "utf-8");
const model = JSON.parse(modelJSON);
const clf = svm.restore(model);

app.get("/api/predict", (req, res) => {
  const px = req.query.px;
  if (!px) {
    res.json({ status: false });
    return;
  }
  const pxa = px.split("").map(v => parseInt("0x" + v) * 16);
  console.log("Data:", pxa.join(":"));
  clf.predict(pxa).then(label => {
    res.json({ status: true, label });
    console.log("Predict:", label);
  });
});

app.use("/", express.static("./public"));
