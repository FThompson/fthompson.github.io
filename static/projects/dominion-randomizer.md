# Dominion Kingdom Randomizer

> Dominion is a deck-building card game created by Donald X. Vaccarino and published by Rio Grande Games. Each player uses a separate deck of cards and draw their hands from their own decks, not others'. Players use the cards in their hands to either perform actions or buy select cards from a common pool of card stacks. The player with the most victory points at the end wins. The game has a "light" medieval theme, with card names that reference pre-industrial, monarchical, and feudal social structures.
>
> -- [WikiPedia article on Dominion](https://en.wikipedia.org/wiki/Dominion_(card_game))

## Motivation

Setup for a game of Dominion involves randomly picking 10 cards that make up the set of cards from which players can buy cards for that game. Each Dominion expansion box adds an additional ~25 card options, so as you purchase additional expansions, it becomes increasingly difficult to shuffle hundreds of possible cards to select just 10 for a game.

## Solution

To address this problem, I created an application to randomize the set of cards based on several user-customized parameters:

 * Which expansions to use
 * Number of cards to draw from each expansion, or relative weights to apply when randomizing
 * Number of cards and special cards total to draw
 * Specific cards to include or exclude
 * Specific card types to exclude

To gather card data, I wrote [a scraper program](https://github.com/FThompson/DominionRandomizer/blob/master/fetch_cards.py) that parses the Dominion Wiki's [List of Cards](http://wiki.dominionstrategy.com/index.php/List_of_cards) into a JSON file.

I first wrote [a version of this program in Python](https://github.com/FThompson/DominionRandomizer), taking randomization parameters as program arguments and outputting selected cards to the console. Desiring something easier to share with my friends and anyone else interested, I then rewrote [the application in JavaScript](https://github.com/dominion-randomizer/dominion-randomizer.github.io) and designed a user interface for selecting randomization options. The live project can be found [here, hosted on GitHub Pages](https://dominion-randomizer.github.io/).

![Web randomizer UI](/static/projects/dominion-randomizer/randomizer-ui.png)

![Example output](/static/projects/dominion-randomizer/example-output.jpg)

## Assets

* [Live Randomizer Web Application](https://dominion-randomizer.github.io/)
* [Web Application Code Repository (JavaScript / HTML / CSS)](https://github.com/dominion-randomizer/dominion-randomizer.github.io)
* [Console Application Code Repository (Python)](https://github.com/FThompson/DominionRandomizer)