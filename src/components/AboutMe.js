import React from 'react';

import '../styles/AboutMe.css';

export default class AboutMe extends React.Component {
  render() {
    return (
      <React.Fragment>
        <h1 id='name'>Hi. I'm <span>Finn Thompson</span>.</h1>
        <h2 id='specialties'>I'm a programmer, UX designer, and tech writer.</h2>
        <p>I am currently looking for work in Seattle as a software developer / tech writer.</p>
        <div id='links'>
          <PrimaryLink
            url='https://github.com/FThompson'
            title='GitHub'
            extension='svg'
            isProfile={true}
          />
          <PrimaryLink
            url='https://stackoverflow.com/users/1247781/fthompson'
            title='StackOverflow'
            label='Stack'
            extension='svg'
            isProfile={true}
          />
          <PrimaryLink
            url='https://www.linkedin.com/in/nnifinn/'
            title='LinkedIn'
            extension='png'
            isProfile={true}
          />
          <PrimaryLink
            url='/static/resume.pdf'
            title='Resume'
            extension='svg'
            isProfile={false}
          />
          <PrimaryLink
            url='mailto:nnifinn@gmail.com'
            title='Email'
            extension='svg'
            isProfile={false}
          />
        </div>
      </React.Fragment>
    );
  }
}

class PrimaryLink extends React.Component {
  render() {
    let imagePath = this.props.title.toLowerCase();
    return (
      <a className='link'
        href={this.props.url}
        title={'View ' + this.props.title + (this.props.isProfile ? ' profile' : '')}
        target='_blank'
      >
        <div>
          <img src={`/static/images/${imagePath}-default.${this.props.extension}`}
            alt={this.props.title}
          />
          <img src={`/static/images/${imagePath}.${this.props.extension}`}
            alt={this.props.title}
          />
        </div>
        <h5>{this.props.label ? this.props.label : this.props.title}</h5>
      </a>
    );
  }
}