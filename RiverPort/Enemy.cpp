#include "Enemy.hpp"
#include <iostream>

Enemy::Enemy(const std::string& filename, int numberOfMap, int x, int y, float lBorder, float rBorder, float shootInterval)
{
	texture.loadFromFile(filename);
	sprite.setTexture(texture);

	//--choose proper map for the level---
	if (numberOfMap == 1)
	{
		for (int i = 0; i < mapHeight; i++)
			map[i] = map1[i];
	}
	else if (numberOfMap == 2)
	{
		for (int i = 0; i < mapHeight; i++)
			map[i] = map2[i];
	}


	leftBorder = lBorder;
	rightBorder = rBorder;
	dtSum = 0;
	frameNumber = 0;
	shootingInterval = shootInterval;
	rect = sf::FloatRect(x, y, humanWidth, humanHeight);
	dx = dy = speed / 2;
	onGround = false;
	side = right;
}

void Enemy::update(sf::Time time)
{
	float dt = time.asSeconds();
	
	if (dtSum > shootingInterval)
	{
		dtSum = 0;
	}

	dtSum += dt;

	rect.left += dx * dt;
	collision(horizontal);

	for (int i = 0; i < bullets.size(); i++)
		bullets[i]->update(dt);

	if (!onGround)
	{
		dy = gravity * dt;
		rect.top += dy;
	}

	onGround = false;
	collision(vertical);

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->isCollided)
		{
			auto delBullet = bullets.begin() + i;
			bullets.erase(delBullet);
		}
	}

	frameNumber += animationSpeed * dt;

	if (frameNumber > 4)
		frameNumber = 0;

	if (side == right)
	{
		if (dx == 0)
			sprite.setTextureRect(sf::IntRect(humanWidth * 2, 0, humanWidth, humanHeight));
		else
			sprite.setTextureRect(sf::IntRect(humanWidth * int(frameNumber), 0, humanWidth, humanHeight));
	}
	if (side == left)
	{
		if (dx == 0)
			sprite.setTextureRect(sf::IntRect(humanWidth * 3, 0, -humanWidth, humanHeight));
		else
			sprite.setTextureRect(sf::IntRect(humanWidth * int(frameNumber) + humanWidth, 0, -humanWidth, humanHeight));
	}

	sprite.setPosition(rect.left, rect.top);
}

void Enemy::collision(int direction)
{
	//-----set walking line--------
	if (direction == vertical)
	{
		//--if in walking segment then go in direction
		if (rect.left > leftBorder && rect.left + rect.width < rightBorder)
		{
			if (side == left)
				dx = -speed / 2;
			else if (side == right)
				dx = speed / 2;
		}
		//--if out of left bound then go right
		else if (rect.left < leftBorder)
		{
			side = right;
			dx = speed / 2;
		}
		//--if out of right bound then go left
		else if (rect.left + rect.width > rightBorder)
		{
			side = left;
			dx = -speed / 2;
		}
	}

	for (int i = rect.top / cellSize; i < (rect.top + rect.height) / cellSize; i++)
	{
		for (int j = rect.left / cellSize; j < (rect.left + rect.width) / cellSize; j++)
		{
			if (map[i][j] == 'B')
			{
				if (direction == horizontal)
				{
					if (dx > 0)
					{
						rect.left = rect.left - rect.width;
					}
					if (dx < 0)
					{
						rect.left = rect.left + cellSize;
					}
				}

				if (direction == vertical)
				{
					if (dy < 0)
						rect.top = i * cellSize + cellSize;
					else if (dy > 0)
					{
						rect.top = i * cellSize - rect.height;
						onGround = true;
					}
					dy = 0;
				}
			}
		}
	}
}

void Enemy::setSpeed(int direction, float pace)
{
	if (direction == vertical)
		dy = pace;
	else if (direction == horizontal)
		dx = pace;
}

sf::Vector2f Enemy::getSpeed()
{
	return sf::Vector2f(dx, dy);
}

sf::FloatRect& Enemy::getRect()
{
	return rect;
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
	for (int i = 0; i < bullets.size(); i++)
		target.draw(*bullets[i], states);
}