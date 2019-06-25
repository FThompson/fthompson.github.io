const webpack = require('webpack');

module.exports = {
  entry: `${__dirname}/src/index.js`,
  output: {
    path: `${__dirname}/dist`,
    publicPath: '/dist/',
    filename: 'bundle.js',
  },

  module: {
    rules: [
      {
        test: /\.js$/, exclude: /node_modules/, loader: 'babel-loader'
      },
      {
        test: /\.html$/, loader: 'html-loader'
      },
      {
        test: /\.css$/, use: [ 'style-loader', 'css-loader' ]
      }
    ],
  }
};