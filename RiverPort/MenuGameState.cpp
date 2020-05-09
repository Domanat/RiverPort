#include "MenuGameState.hpp"
#include "ActionGameState.hpp"
#include "SelectionGameState.hpp"
#include "Constants.hpp"
#include <SFML/Audio.hpp>
#include <iostream>

MenuGameState::MenuGameState(Game* g)
{
	game = g;
	font.loadFromFile("fonts/MenuFont.ttf");
	startString.setFont(font);
	startString.setString("Start Game");
	startString.setCharacterSize(100);
	startString.setFillColor(sf::Color(255, 204, 102));	
	startString.setPosition(450, 50);
	startString.setOutlineColor(sf::Color::Black);
	startString.setOutlineThickness(0.f);

	levelString.setFont(font);
	levelString.setString("Choose level");
	levelString.setCharacterSize(100);
	levelString.setFillColor(sf::Color(255, 204, 102));
	levelString.setPosition(445, 150);
	levelString.setOutlineColor(sf::Color::Black);
	levelString.setOutlineThickness(0.f);

	backTexture.loadFromFile("images/MenuBackground.png");
	background.setTexture(backTexture);

	music.openFromFile("music/CountryRoads.wav");
	music.setVolume(10);
	music.setLoop(true);
	music.play();
}

void MenuGameState::input()
{
	sf::Event event;
	while (game->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			game->window.close();	

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left && startString.getGlobalBounds().contains(sf::Vector2f(mousePos)))
			{
				game->changeState(new ActionGameState(game, 1));
			}

			if (event.mouseButton.button == sf::Mouse::Left && levelString.getGlobalBounds().contains(sf::Vector2f(mousePos)))
			{
				game->changeState(new SelectionGameState(game));
			}
		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		game->window.close();
}

void MenuGameState::update(sf::Time dt)
{
	mousePos = sf::Mouse::getPosition(game->window);
	startString.setOutlineThickness(0.f);
	levelString.setOutlineThickness(0.f);
	if (startString.getGlobalBounds().contains(sf::Vector2f(mousePos)))
	{
		startString.setOutlineThickness(1.f);
	}
	else if (levelString.getGlobalBounds().contains(sf::Vector2f(mousePos)))
	{
		levelString.setOutlineThickness(1.f);
	}
}

void MenuGameState::draw()
{
	game->window.clear();
	game->window.draw(background);
	game->window.draw(startString);
	game->window.draw(levelString);

	game->window.display();
}