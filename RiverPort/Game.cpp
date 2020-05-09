#include "Game.hpp"
#include "GameState.hpp"
#include "MenuGameState.hpp"
#include <iostream>

Game::Game() :
	window(sf::VideoMode(windowWidth, windowHeight), "RiverPort")
{
	pushState(new MenuGameState(this));
}

Game::~Game()
{
	while (!states.empty())
		states.pop();
}

void Game::start()
{
	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Time dt = clock.restart();

		if (dt.asSeconds() > 0.009)
			continue;

		if (peekState() == nullptr)
			continue;

		peekState()->input();
		peekState()->update(dt);
		peekState()->draw();
	}
}

void Game::pushState(GameState* state)
{
	states.push(state);
}

void Game::popState()
{
	states.pop();
}

GameState* Game::peekState()
{
	return states.empty() ? nullptr : states.top();
}

void Game::changeState(GameState* state)
{
	if (!states.empty())
		states.pop();

	states.push(state);
}
