#ifndef ENEMY_H
#define ENEMY_H

#include "Constants.hpp"
#include "Entity.hpp"
#include "Bullet.hpp"

class Enemy : public Entity
{
private:
	sf::String map[mapHeight];

public:
	float leftBorder, rightBorder;
	int side;
	float shootingInterval;
	float dtSum;
	std::vector<Bullet*> bullets;

	Enemy(const std::string& filename, int numberOfMap, int x, int y, float lBorder, float rBorder, float shootingInterval);

	virtual void update(sf::Time dt) override;
	void collision(int direction);
	void setSpeed(int direction, float dy);
	sf::Vector2f getSpeed();

	virtual sf::FloatRect& getRect() override;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif