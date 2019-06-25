/**
 * This gulp file converts project pages, written in markdown, to HTML.
 * The default task additional watches the markdown folder for changes.
 */

const path = require('path');
const gulp = require('gulp');
const through = require('through2');
const showdown = require('showdown');
const del = require('del');

const markdownSrc = 'src/projects';
const htmlDest = 'dist/projects';

function watchMarkdown() {
  let markdownWatcher = gulp.watch([`${markdownSrc}/*.md`]);
  markdownWatcher.on('change', (patharg, stats) => {
    convertMarkdown(null, patharg);
  });
  markdownWatcher.on('add', (patharg, stats) => {
    convertMarkdown(null, patharg);
  });
  markdownWatcher.on('unlink', (patharg, stats) => {
    let filepath = path.parse(patharg);
    let htmlPath = `${htmlDest}/${filepath.name}.html`;
    del(htmlPath);
  });
}

function convertMarkdown(callback, src=`${markdownSrc}/*.md`) {
  gulp.src(src, { base: markdownSrc })
    .pipe(convertMarkdownToHTML())
    .pipe(gulp.dest(`${htmlDest}/`));
  if (callback) {
    callback();
  }
}

function convertMarkdownToHTML() {
  let converter = new showdown.Converter();
  converter.setOption('noHeaderId', true);
  converter.setOption('openLinksInNewWindow', true);
  return through.obj(function(file, encoding, callback) {
    let newFile = file.clone();
    newFile.extname = '.html';
    let markdown = file.contents.toString();
    let html = converter.makeHtml(markdown);
    newFile.contents = Buffer.from(html, encoding);
    this.push(newFile);
    callback(null, newFile);
  });
}

exports.build = convertMarkdown;
exports.default = gulp.parallel(convertMarkdown, watchMarkdown);