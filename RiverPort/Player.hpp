#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Constants.hpp"
#include "Bullet.hpp"
#include <vector>

class Player : public Entity
{
private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void collision(int direction);

	sf::String map[mapHeight];
	sf::RenderWindow& window;
	sf::Vector2f mousePos;

	bool isShooting;

public:
	std::vector<Bullet*> bullets;
	int side;
	int score;
	int lifes;

	Player(const std::string& filename, sf::RenderWindow& win, int currentMap);

	virtual void update(sf::Time dt) override;
	void input();
	
	sf::Vector2f getPosition();
	sf::Vector2f getSpeed();
	void setSpeed(int direction, float pace);
	virtual sf::FloatRect& getRect() override;
	
};

#endif