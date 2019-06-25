import React from 'react';
import Project from './Project';
import { projects } from './../projects/projects.json';

import '../styles/ProjectsView.css';

export default class ProjectsView extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      filter: 'All'
    };
    this.setFilter = this.setFilter.bind(this);
  }

  setFilter(tag) {
    this.setState({ filter: tag });
  }

  render() {
    let filteredProjects = projects;
    if (this.state.filter !== 'All') {
      filteredProjects = projects.filter(project => {
        return project.tags.some(tag => tag === this.state.filter);
      });
    }
    return (
      <section id='projects-container'>
        <h2 id='projects-label'>Projects</h2>
        <div id='project-filters'>
          <span>Show projects tagged:</span>
          <ProjectFilter
            id='all'
            label='All'
            onFilterChange={this.setFilter}
          />
          <ProjectFilter
            id='programming'
            label='Programming'
            onFilterChange={this.setFilter}
          />
          <ProjectFilter
            id='ui-ux'
            label='UI/UX'
            onFilterChange={this.setFilter}
          />
          <ProjectFilter
            id='tech-writing'
            label='Tech Writing'
            onFilterChange={this.setFilter}
          />
        </div>
        <div id='projects'>
          {filteredProjects.map(project =>
            <Project key={project.title} {...project} />
          )}
          {/* project spacers impact constant width to projects on the last row */}
          <div className='project project-spacer'></div>
          <div className='project project-spacer'></div>
        </div>
      </section>
    );
  }
}

class ProjectFilter extends React.Component {
  constructor(props) {
    super(props);
    this.handleChange = this.handleChange.bind(this);
  }

  handleChange(e) {
    this.props.onFilterChange(e.target.value);
  }

  render() {
    return (
      <React.Fragment>
        <input type='radio'
          name='filter'
          id={this.props.id}
          value={this.props.label}
          onChange={this.handleChange}
          defaultChecked={this.props.id === 'all'}
        />
        <label htmlFor={this.props.id}>{this.props.label}</label>
      </React.Fragment>
    );
  }
}