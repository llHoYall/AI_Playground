const fs = require("fs");
const path = require("path");

convertToCSV(path.join(__dirname, "database"));

function convertToCSV(dir) {
  const imgFile = path.join(dir, "images-idx3");
  const labelFile = path.join(dir, "labels-idx1");
  const csvFile = path.join(dir, "images.csv");

  const imgFd = fs.openSync(imgFile, "r");
  const labelFd = fs.openSync(labelFile, "r");
  const csvFd = fs.openSync(csvFile, "w+");

  const imgFileBuf = Buffer.alloc(16);
  fs.readSync(imgFd, imgFileBuf, 0, imgFileBuf.length);
  const imgMagicNumber = imgFileBuf.readUInt32BE(0);
  const numImages = imgFileBuf.readUInt32BE(4);
  const numRows = imgFileBuf.readUInt32BE(8);
  const numCols = imgFileBuf.readUInt32BE(12);
  const numPixels = numRows * numCols;
  if (imgMagicNumber !== 2051) throw new Error("Broken file");
  console.log("Number of Images =", numImages, numRows, "x", numCols);

  const labelFileBuf = Buffer.alloc(8);
  fs.readSync(labelFd, labelFileBuf, 0, labelFileBuf.length);
  const labelMagicNumber = labelFileBuf.readUInt32BE(0);
  if (labelMagicNumber !== 2049) throw new Error("Broken file");

  const pixels = Buffer.alloc(numPixels);
  const labelBuf = Buffer.alloc(1);
  for (let i = 0; i < numImages; ++i) {
    if (i % 1000 === 0) console.log(i + " / " + numImages);

    fs.readSync(imgFd, pixels, 0, numPixels);
    fs.readSync(labelFd, labelBuf, 0, 1);
    const line = new Uint8Array(pixels);
    const label = labelBuf.readInt8(0);

    if (i < 20) {
      let s = "P2 28 28 255\n";
      for (let j = 0; j < numPixels; ++j) {
        s += line[j].toString();
        s += j % 28 === 27 ? "\n" : " ";
      }
      const saveFile = path.join(dir, i + "_test_" + label + ".pgm");
      fs.writeFileSync(saveFile, s, "utf-8");
    }
    const csvLine = label + "," + line.join(",") + "\n";
    fs.writeSync(csvFd, csvLine, "utf-8");
  }
  console.log("OK");
}
