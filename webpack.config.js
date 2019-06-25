const webpack = require('webpack');
const production = process.argv.indexOf('-p') !== -1;

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
    ]
  },

  plugins: !production ? [] : [
    new webpack.DefinePlugin({
      'process.env.NODE_ENV': JSON.stringify('production')
    })
  ]
};