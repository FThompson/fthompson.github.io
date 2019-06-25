import React from 'react';
import { Link } from 'react-router-dom';

export default class Project extends React.Component {
  render() {
    let teamLabel = 'Team: ' + this.props.team;
    return (
      <section className='project'>
        <h3>{this.props.title}</h3>
        <div className='tags'>
          {this.props.tags.map(tag =>
            <span className='tag' key={tag}>{tag}</span>
          )}
        </div>
        <p dangerouslySetInnerHTML={{__html: this.props.summary}}></p>
        {this.props.report &&
          <a href={`/static/projects/reports/${this.props.report}`}
            title={`View report for ${this.props.title}`}
            target='_blank'
            rel='noopener noreferrer'
          >View report</a>
        }
        {this.props.content &&
          <Link to={{ pathname: this.props.content }}
            title={`Read more about ${this.props.title}`}
          >
            Read more
          </Link>
        }
        <div className='bottom'>
          <span>{this.props.date}</span>
          {this.props.github &&
            <ProjectIconLink
              url={this.props.github}
              iconClass='project-github'
              title={`View source code of ${this.props.title}`}
            />
          }
          {this.props.external &&
            <ProjectIconLink
              url={this.props.external}
              iconClass='project-external-link'
              title={`View external link for ${this.props.title}`}
            />
          }
          {this.props.team > 1 &&
            <img className='project-icon'
              src='/static/images/multiple-users.svg'
              alt={teamLabel}
              title={teamLabel}
            />
          }
        </div>
      </section>
    );
  }
}

function ProjectIconLink(props) {
  return (
    <a className={`project-icon ${props.iconClass}`}
      href={props.url}
      title={props.title}
      target='_blank'
      rel='noopener noreferrer'
    ></a>
  );
}