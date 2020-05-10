#ifndef VICTORY_GAME_STATE_HPP
#define VICTORY_GAME_STATE_HPP

#include "GameState.hpp"

class VictoryGameState : public GameState
{
private:
	sf::View view;
	sf::Font font;
	sf::Text ChooseLevel;
	sf::Text winText;
public:
	VictoryGameState(Game* g);

	virtual void input();
	virtual void update(sf::Time dt);
	virtual void draw();

};

#endif