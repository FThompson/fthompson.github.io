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

    }
    if (project.external) {

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
        $('#projects').hide()
        projectPage.show()
    })
}

function closeProjectPage() {
    $('#project-page').hide()
    $('#projects').show()
    document.title = 'Finn Thompson - Portfolio'
}

function changeView() {
    if (window.location.hash) {
        let content = window.location.hash.slice(3) + '.md'
        openProjectPage(content)
    } else {
        closeProjectPage()
    }
}