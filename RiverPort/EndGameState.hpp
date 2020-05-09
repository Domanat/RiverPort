#ifndef END_GAME_STATE_HPP
#define END_GAME_STATE_HPP

#include <SFML/Audio.hpp>
#include "GameState.hpp"

class EndGameState : public GameState
{
private:
	sf::Music music;

	sf::View view;
	sf::Font font;
	sf::Text tryAgain;	

public:
	EndGameState(Game* g);

	virtual void input();
	virtual void update(sf::Time dt);
	virtual void draw();
};

#endif 