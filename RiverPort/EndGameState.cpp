#include "EndGameState.hpp"
#include "SelectionGameState.hpp"

EndGameState::EndGameState(Game* g)
{
	game = g;
	view = game->window.getDefaultView();
	game->window.setView(view);
	
	backTexture.loadFromFile("images/TheEnd.png");
	background.setTexture(backTexture);
	background.setPosition(0, 0);

	font.loadFromFile("fonts/MainFont.ttf");
	tryAgain.setFont(font);
	tryAgain.setCharacterSize(100);
	tryAgain.setString("Try Again");
	tryAgain.setFillColor(sf::Color(255, 153, 51));
	tryAgain.setPosition(450, 400);
	tryAgain.setOutlineColor(sf::Color::White);
	tryAgain.setOutlineThickness(0.f);
}

void EndGameState::input()
{
	sf::Event event;

	while (game->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			game->window.close();

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			game->window.close();


		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left && tryAgain.getGlobalBounds().contains(sf::Vector2f(mousePos)))
			{
				game->changeState(new SelectionGameState(game));
			}
		}
	}
}

void EndGameState::update(sf::Time time)
{
	float dt = time.asSeconds();

	mousePos = sf::Mouse::getPosition(game->window);
	tryAgain.setOutlineThickness(0.f);
	
	if (tryAgain.getGlobalBounds().contains(sf::Vector2f(mousePos)))
	{
		tryAgain.setOutlineThickness(1.f);
	}
}

void EndGameState::draw()
{
	game->window.setView(view);
	game->window.clear();
	game->window.draw(background);
	game->window.draw(tryAgain);
	game->window.display();
}