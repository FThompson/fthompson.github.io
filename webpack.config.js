const webpack = require('webpack');
const HtmlWebpackPlugin = require('html-webpack-plugin');

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
  },

  plugins: [
    new HtmlWebpackPlugin({
      template: `${__dirname}/index.html`,
      filename: `${__dirname}/index.html`,
      favicon: `${__dirname}/static/favicons/favicon.ico`
    })
  ],
};