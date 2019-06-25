import React from 'react';
import Header from './Header';

import '../styles/ProjectPage.css';

export default class ProjectPage extends React.Component {
  constructor(props) {
    super(props);
    // load HTML generated from markdown source files with gulp and showdown
    try {
      this.html = require(`../../dist/projects/${props.match.params.project}.html`);
    } catch (e) {
      // unable to find page, need to show 404
      this.html = null;
    }
  }

  componentWillMount() {
    if (this.html) {
      // extract main heading text to be used as title
      let firstLine = this.html.substring(0, this.html.indexOf('\n'));
      let title = firstLine.replace(/<\/?h\d>/g, '');
      document.title = `Finn Thompson - ${title}`;
    }
  }

  componentDidMount() {
    window.scrollTo(0, 0);
  }

  render() {
    return (
      <React.Fragment>
        <Header small={true} />
        {this.html !== null ?
          <div id='project-page'
            dangerouslySetInnerHTML={{ __html: this.html }}
          ></div>
        :
          <PageNotFound {...this.props} />
        }
      </React.Fragment>
    )
  }
}

class PageNotFound extends React.Component {
  componentWillMount() {
    document.title = `Finn Thompson - Page not found`;
  }

  render() {
    return (
      <h3 id='page404'>Project not found (HTML 404) at {this.props.location.pathname}.</h3>
    );
  }
}