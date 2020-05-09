#include "SelectionGameState.hpp"
#include <iostream>

SelectionGameState::SelectionGameState(Game* g) :
	firstLevel("1", 100, 50),
	secondLevel("2", 400, 50)
{
	game = g;

	backTexture.loadFromFile("images/MenuBackground.png");
	background.setTexture(backTexture);

}

void SelectionGameState::input()
{
	sf::Event event;
	while (game->window.pollEvent(event))
	{ 
		if (event.type == sf::Event::Closed)
			game->window.close();

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left && firstLevel.rect.getGlobalBounds().contains(sf::Vector2f(mousePos)))
			{
				game->changeState(new ActionGameState(game, 1));
			}/*
			if (event.mouseButton.button == sf::Mouse::Left && secondLevel.rect.getGlobalBounds().contains(sf::Vector2f(mousePos)))
			{
				game->changeState(new ActionGameState(game, 2));
			}*/
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		game->window.close();
}

void SelectionGameState::update(sf::Time dt)
{
	mousePos = sf::Mouse::getPosition(game->window);
	
	firstLevel.rect.setOutlineThickness(0.f);
	secondLevel.rect.setOutlineThickness(0.f);
	if (firstLevel.rect.getGlobalBounds().contains(sf::Vector2f(mousePos)))
	{
		firstLevel.rect.setOutlineThickness(1.f);
	}
	if (secondLevel.rect.getGlobalBounds().contains(sf::Vector2f(mousePos)))
	{
		secondLevel.rect.setOutlineThickness(1.f);
	}
}


void SelectionGameState::draw()
{
	game->window.clear();
	game->window.draw(background);

	//---Draw levels' buttons 
	game->window.draw(firstLevel);
	//game->window.draw(secondLevel);

	game->window.display();
}