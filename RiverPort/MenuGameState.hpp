#ifndef MENU_GAME_STATE_HPP
#define MENU_GAME_STATE_HPP

#include "GameState.hpp"
#include <SFML/Audio.hpp>

class MenuGameState : public GameState
{
private:
	sf::Music music;

	sf::Text startString;
	sf::Text levelString;
	sf::Font font;

public:

	MenuGameState(Game* game);

	virtual void draw();
	virtual void update(sf::Time dt);
	virtual void input();

};

#endif