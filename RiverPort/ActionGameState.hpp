#ifndef ACTION_GAME_STATE_HPP
#define ACTION_GAME_STATE_HPP

#include "GameState.hpp"
#include <SFML/Audio.hpp>
#include <vector>

class ActionGameState : public GameState
{
private:
	sf::View view;

	//------Change all that textures on texture manager!!---------------------

	//textures for block which we use to draw level;
	sf::Texture drawBlockTexture;
	sf::Sprite drawBlock;

	sf::Texture coinTexture;
	sf::Sprite coin;

	//------------------------------------------------------------------
	sf::Font generalFont;
	sf::Text score;
	sf::Text lifes;

	sf::String map[21];

	Player player;
	std::vector<Enemy*> enemies;

public:

	ActionGameState(Game* game, int numberOfMap);

	void objectsCollision(int direction);
	void playerObjectCollision();
	void bulletBorderCollision(Bullet* bullet);
	void enemySeePlayer(Enemy* enemy);
	virtual void input();
	virtual void update(sf::Time dt);
	virtual void draw();

	~ActionGameState();
};

#endif