#include "Player.hpp"
#include <iostream>

Player::Player(const std::string& filename, sf::RenderWindow& win, int currentMap)
	: window(win)
{
	texture.loadFromFile(filename);
	sprite.setTexture(texture);

	isShooting = true;
	lifes = 3;

	rect = sf::FloatRect(9 * cellSize, 8 * cellSize, humanWidth, humanWidth);

	if (currentMap == 1)
	{
		for (int i = 0; i < mapHeight; i++)
		{
			map[i] = map1[i];
		}
	}
	else if (currentMap == 2)
	{
		
	}

	score = 0;
	dx = dy = speed;
	frameNumber = 0;
	onGround = false;
}

void Player::input()
{

	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	mousePos = window.mapPixelToCoords(pixelPos);

	if (rect.left - mousePos.x < 0)
		side = right;
	else if (rect.left - mousePos.x > 0)
		side = left;
	else
		side = right;

	//shoot bullet
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//check for one click
		if (!isShooting)
		{
			//shot looking to the left
			if (side == left)
				bullets.push_back(new Bullet(rect.left, rect.top + 10, left));
			if (side == right)
				bullets.push_back(new Bullet(rect.left + rect.width, rect.top + 10, right));
			isShooting = true;
		}

	}
	else
		isShooting = false;


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		dx = speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		dx = -speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (onGround)
		{
			dy = -jumpSpeed;
			onGround = false;
		}
	}

	
}

void Player::update(sf::Time time)
{
	float dt = time.asSeconds();
	rect.left += dx * dt;
	collision(horizontal);
	

	for (int i = 0; i < bullets.size(); i++)
		bullets[i]->update(dt);


	if (!onGround)
	{
		dy += gravity * dt;
		rect.top += dy * dt;
	}

	onGround = false;
	collision(vertical);

	frameNumber += animationSpeed * dt;

	if (frameNumber > 4)
		frameNumber = 0;

	//check bullets existence
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->isCollided)
		{
			auto delBullet = bullets.begin() + i;
			bullets.erase(delBullet);
		}
	}

	//right
	if (side == right)
	{
		sprite.setTextureRect(sf::IntRect(humanWidth * int(frameNumber), 0, humanWidth, humanHeight));
	
		if (dx == 0)
			sprite.setTextureRect(sf::IntRect(128, 0, humanWidth, humanHeight));
	}
	//left
	else if (side == left)
	{
		sprite.setTextureRect(sf::IntRect(humanWidth * int(frameNumber) + humanWidth, 0, -humanWidth, humanHeight));
	
		if (dx == 0)
			sprite.setTextureRect(sf::IntRect(128 + humanWidth, 0, -humanWidth, humanHeight));
	}
	
	dx = 0;
	sprite.setPosition(rect.left, rect.top);
}

void Player::collision(int direction)
{
	for (int i = rect.top / cellSize; i < (rect.top + rect.height) / cellSize; i++)
	{
		for (int j = rect.left / cellSize; j < (rect.left + rect.width) / cellSize; j++)
		{
			if (map[i][j] == 'B')
			{
				if (direction == horizontal)
				{
					if (dx > 0)
						rect.left = j * cellSize - rect.width;
					else if (dx < 0)
						rect.left = j * cellSize + cellSize;
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

sf::FloatRect& Player::getRect()
{
	return rect;
}

sf::Vector2f Player::getSpeed()
{
	return sf::Vector2f(dx, dy);
}

void Player::setSpeed(int direction, float pace)
{
	if (direction == vertical)
		dy = pace;
	else if (direction == horizontal)
		dx = pace;
}

sf::Vector2f Player::getPosition()
{
	return sprite.getPosition();
}


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	
	target.draw(sprite, states);
	for (int i = 0; i < bullets.size(); i++)
		target.draw(*bullets[i], states);
}