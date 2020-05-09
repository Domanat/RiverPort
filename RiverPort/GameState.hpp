#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "Game.hpp"

class GameState
{
public:
	Game* game;
	sf::Vector2i mousePos;

	//------will be changed to a textureManager----------------
	//Background image
	sf::Texture backTexture;
	sf::Sprite background;

	virtual void draw() = 0;
	virtual void update(sf::Time dt) = 0;
	virtual void input() = 0;
};

#endif