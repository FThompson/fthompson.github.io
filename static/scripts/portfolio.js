changeView()
fetch('static/projects/projects.json').then(response => response.json()).then(data => {
    data.projects.forEach(addProject)
})
$(window).on('hashchange', changeView)

function addProject(project) {
    let card = $('<div>').addClass('project').appendTo($('#projects'))
    $('<h3>').text(project.title).appendTo(card)
    let tagsDiv = $('<div>').addClass('tags').appendTo(card)
    project.tags.forEach(tag => {
        $('<span>').addClass('tag').text(tag).appendTo(tagsDiv)
    })
    $('<p>').html(project.summary).appendTo(card)
    if (project.content) {
        // TODO: convert site to jekyll or other solution to avoid hashbang usage
        let hash = '#!/' + project.content.slice(0, project.content.length - 3)
        $('<a>').attr('href', hash).attr('title', 'Expand').text('Read more').appendTo(card)
    }
    let bottom = $('<div>').addClass('bottom').appendTo(card)
    $('<span>').text(project.date).appendTo(bottom)
    if (project.github) {
        createImageLink(project.github, 'project-github', 'View source code').appendTo(bottom)
    }
    if (project.external) {
        createImageLink(project.external, 'project-external-link', 'View project').appendTo(bottom)
    }
    if (project.team > 1) {
        let label = 'Team: ' + project.team
        $('<img>').addClass('project-icon').attr('src', '/static/images/multiple-users.svg')
                .attr('alt', label).attr('title', label).appendTo(bottom)
    }
}

function openProjectPage(markdownLink) {
    let projectPage = $('#project-page')
    projectPage.empty()
    fetch('static/projects/' + markdownLink).then(response => response.text()).then(text => {
        let converter = new showdown.Converter()
        let html = converter.makeHtml(text)
        projectPage.append(html)
        let title = projectPage.children().first().text()
        document.title = document.title.replace('Portfolio', title)
        $('#landing').hide()
        projectPage.show()
    })
}

function closeProjectPage() {
    $('#project-page').empty().hide()
    $('#landing').show()
    document.title = 'Finn Thompson - Portfolio'
}

function changeView() {
    if (window.location.hash) {
        openProjectPage(window.location.hash.slice(3) + '.md')
    } else {
        closeProjectPage()
    }
}

function createImageLink(link, imageClass, title) {
    return $('<a>').addClass('project-icon').addClass(imageClass).attr('href', link).attr('title', title)
            .attr('target', '_blank')
}