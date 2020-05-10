#include "VictoryGameState.hpp"
#include "SelectionGameState.hpp"

VictoryGameState::VictoryGameState(Game* g)
{
	game = g;

	view = game->window.getDefaultView();
	game->window.setView(view);

	backTexture.loadFromFile("images/VictoryBackground.png");
	background.setTexture(backTexture);
	background.setPosition(0, 0);
	
	font.loadFromFile("fonts/MainFont.ttf");
	winText.setFont(font);
	winText.setCharacterSize(100);
	winText.setString("You win!");
	winText.setFillColor(sf::Color::Black);
	winText.setPosition(450, 20);

	ChooseLevel.setFont(font);
	ChooseLevel.setCharacterSize(100);
	ChooseLevel.setString("Choose Level");
	ChooseLevel.setFillColor(sf::Color::Black);
	ChooseLevel.setPosition(350, 100);
	ChooseLevel.setOutlineColor(sf::Color::Blue);
	ChooseLevel.setOutlineThickness(0.f);
}


void VictoryGameState::input()
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
			if (event.mouseButton.button == sf::Mouse::Left && ChooseLevel.getGlobalBounds().contains(sf::Vector2f(mousePos)))
			{
				game->changeState(new SelectionGameState(game));
			}
		}
	}
}

void VictoryGameState::update(sf::Time time)
{
	mousePos = sf::Mouse::getPosition(game->window);
	ChooseLevel.setOutlineThickness(0.f);

	if (ChooseLevel.getGlobalBounds().contains(sf::Vector2f(mousePos)))
	{
		ChooseLevel.setOutlineThickness(1.f);
	}
}

void VictoryGameState::draw()
{
	game->window.setView(view);
	game->window.clear();
	game->window.draw(background);
	game->window.draw(ChooseLevel);
	game->window.draw(winText);
	game->window.display();

}