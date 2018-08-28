const path = require("path");

module.exports = {
  mode: "development",
  entry: path.join(__dirname, "7-client.js"),
  output: {
    path: path.join(__dirname, "public"),
    filename: "bundle.js"
  },
  devtool: "inline-source-map",
  module: {
    rules: [
      {
        test: /.js$/,
        loader: "babel-loader",
        options: {
          presets: ["env", "react"]
        }
      }
    ]
  }
};
