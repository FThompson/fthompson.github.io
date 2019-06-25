import React from 'react';
import { Link } from 'react-router-dom';

export default class Header extends React.Component {
  render() {
    return (
      <React.Fragment>
        <header></header>
        <Link id='profile'
          className={this.props.small ? 'small' : ''}
          to={{ pathname: '/' }}
          title='Portfolio Home'
        />
      </React.Fragment>
    );
  }
}