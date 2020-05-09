#ifndef SELECTION_GAME_STATE
#define SELECTION_GAME_STATE

#include "ActionGameState.hpp"
#include "GameState.hpp"

class Level : public sf::Drawable
{
public:
	sf::Text text;
	sf::RectangleShape rect;
	sf::Font font;
	Level(const std::string& str, int x, int y)
	{
		rect.setSize(sf::Vector2f(100, 100));
		rect.setFillColor(sf::Color(255, 153, 0));
		rect.setOutlineColor(sf::Color::Blue);
		rect.setOutlineThickness(0.f);
		rect.setPosition(x, y);

		font.loadFromFile("fonts/MainFont.ttf");
		text.setFont(font);
		text.setString(str);
		text.setCharacterSize(50);
		text.setFillColor(sf::Color(255, 102, 102));
		text.setPosition(rect.getPosition().x + 40, rect.getPosition().y + 20);
		
	}
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(rect, states);
		target.draw(text, states);
	}
};

class SelectionGameState : public GameState
{
private:

	Level firstLevel;
	Level secondLevel;

public:

	SelectionGameState(Game* game);

	virtual void input();
	virtual void update(sf::Time dt);
	virtual void draw();
};

#endif