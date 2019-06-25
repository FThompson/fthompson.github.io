import React from 'react';
import AboutMe from './AboutMe';
import ProjectsView from './ProjectsView';
import Header from './Header';

export default class Home extends React.Component {
  componentWillMount() {
    document.title = 'Finn Thompson - Portfolio';
  }

  render() {
    return (
      <React.Fragment>
        <Header small={false} />
        <div id='landing'>
          <AboutMe />
          <ProjectsView />
        </div>
      </React.Fragment>
    );
  }
}