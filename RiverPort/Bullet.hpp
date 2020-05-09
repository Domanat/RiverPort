#ifndef BULLET_HPP
#define BULLET_HPP

#include "Entity.hpp"
#include "Constants.hpp"

class Bullet : public sf::Drawable
{
private:
	float dx, dy;
	int direction;
	sf::FloatRect rect;

	sf::RectangleShape shape;
public:
	Bullet(int x, int y, int direction);


	bool isCollided;
	void update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::FloatRect& getRect();
	sf::RectangleShape& getShape();

	void setSpeed(float dx, float dy);
	sf::Vector2f getSpeed();
};

#endif 