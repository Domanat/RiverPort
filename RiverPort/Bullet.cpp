#include "Bullet.hpp"

Bullet::Bullet(int x, int y, int direction)
{
	isCollided = false;

	shape.setSize(sf::Vector2f(bulletWidth, bulletHeight));
	shape.setPosition(x, y);
	shape.setFillColor(sf::Color(255, 255, 0));

	//left
	if (direction == left)
		dx = -speed * 1.5;
	//right
	else if (direction == right)
		dx = speed * 1.5;
	dy = 0;
	rect = sf::FloatRect(x, y, bulletWidth, bulletHeight);
}

void Bullet::update(float dt)
{
	if (isCollided)
		return;

	rect.left += dx * dt;

	shape.setPosition(sf::Vector2f(rect.left, rect.top));
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
}

sf::RectangleShape& Bullet::getShape()
{
	return shape;
}

void Bullet::setSpeed(float dx, float dy)
{
	this->dx = dx;
	this->dy = dy;
}

sf::Vector2f Bullet::getSpeed()
{
	return sf::Vector2f(dx, dy);
}

sf::FloatRect& Bullet::getRect()
{
	return rect;
}