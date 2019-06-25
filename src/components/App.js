import React from 'react';
import { BrowserRouter } from 'react-router-dom';
import { Switch, Route } from 'react-router-dom';

import Footer from './Footer';
import Home from './Home';
import ProjectPage from './ProjectPage';

import '../styles/App.css';

export default class App extends React.Component {
  render() {
    return (
      <BrowserRouter>
        <Switch>
          <Route exact path='/' component={Home}></Route>
          <Route path='/:project' component={ProjectPage}></Route>
        </Switch>
        <Footer />
      </BrowserRouter>
    );
  }
}