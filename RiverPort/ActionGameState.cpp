#include "ActionGameState.hpp"
#include <iostream>
#include "EndGameState.hpp"

ActionGameState::ActionGameState(Game* g, int numberOfMap) :
	player("images/Player.png", g->window, numberOfMap)
{	
	game = g;

	//----extract the right map
	if (numberOfMap == 1)
	{
		for (int i = 0; i < mapHeight; i++)
		{
			map[i] = map1[i];
		}

		//---choose proper background
		if (!backTexture.loadFromFile("images/GameBackground2.png"))
		{
			std::cout << "ERROR: Can't load background texture " << std::endl;
		}
		background.setTexture(backTexture);

		if (!coinTexture.loadFromFile("images/Bottle.png"))
		{
			std::cout << "ERROR: Can't load coin texture" << std::endl;
		}
		coin.setTexture(coinTexture);

		//brick on the level
		if (!drawBlockTexture.loadFromFile("images/sand.png"))
		{
			std::cout << "ERROR: can't load drawBlockTexture" << std::endl;
		}
		drawBlock.setTexture(drawBlockTexture);

		//-------------------Enemy(loadfile, numberOfMap, X pos, Y pos, Left Border, Right Border, shootInterval(normal = 0.1))---------------
		enemies.push_back(new Enemy("images/Enemy.png", 1, 10 * cellSize, 10 * cellSize, 2 * cellSize, 20 * cellSize, 0.1));
		enemies.push_back(new Enemy("images/Enemy.png", 1, 20 * cellSize, 19 * cellSize, 15 * cellSize, 35 * cellSize, 0.2));
		enemies.push_back(new Enemy("images/Enemy.png", 1, 15 * cellSize, 13 * cellSize, 14 * cellSize, 22 * cellSize, 0.3));
	}
	else if (numberOfMap == 2)
	{

	}
	
	//generalFont.loadFromFile("fonts/MenuFont.ttf");
	//score.setFont(generalFont);
	//score.setCharacterSize(50);
	//score.setFillColor(sf::Color::Black);
	//score.setOutlineColor(sf::Color::Green);
	//score.setOutlineThickness(1.f);
	//score.setPosition(0, 0);
	//score.setString("Score: "); //put at 350, 0

	//lifes.setFont(generalFont);
	//lifes.setCharacterSize(50);
	//lifes.setFillColor(sf::Color::Black);
	//lifes.setOutlineColor(sf::Color::Green);
	//lifes.setOutlineThickness(1.f);
	//lifes.setPosition(60, 0);
	//lifes.setString("Lifes: "); //put at 350, 60

	view.setSize(sf::Vector2f(windowWidth, windowHeight));
}

void ActionGameState::input()
{
	sf::Event event;

	while (game->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			game->window.close();

		if (event.key.code == sf::Keyboard::Escape)
			game->window.close();
	}

	player.input();
}
		
void ActionGameState::update(sf::Time dt)
{
	if (player.lifes == 0)
		game->changeState(new EndGameState(game));

	player.update(dt);
	
	for (int i = 0; i < enemies.size(); i++)
		enemies[i]->update(dt);

	//enemy and player collision
	for (int i = 0; i < enemies.size(); i++)
	{
		if (player.getRect().intersects(enemies[i]->getRect()))
		{
			if (player.getSpeed().y > 0)
				player.setSpeed(vertical, -jumpSpeed);
		}
		enemySeePlayer(enemies[i]);
	}

	// player collision with coins for example
	playerObjectCollision();

	//add bullet collision with enemies and borders
	objectsCollision(horizontal);

	//center view to the player;
	view.setCenter(player.getPosition().x, player.getPosition().y);
	game->window.setView(view);
			
	//set background image correct
	background.setPosition(view.getCenter().x - windowWidth / 2, view.getCenter().y - windowHeight / 2);
}

void ActionGameState::playerObjectCollision()
{
	for (int i = player.getRect().top / cellSize; i < (player.getRect().top + player.getRect().height) / cellSize; i++)
	{
		for (int j = player.getRect().left / cellSize; j < (player.getRect().left + player.getRect().width) / cellSize; j++)
		{
			if (map[i][j] == 'C')
			{
				map[i][j] = ' ';
				player.score++;
			}
			//something else 
		}
	}
}

void ActionGameState::enemySeePlayer(Enemy* enemy)
{
	//enemy look on the left or right and sees player
	if (player.getRect().top == enemy->getRect().top && player.getRect().left > enemy->leftBorder
		&& player.getRect().left <= enemy->getRect().left && enemy->side == left || player.getRect().top == enemy->getRect().top && player.getRect().left < enemy->rightBorder
		&& player.getRect().left >= enemy->getRect().left && enemy->side == right)
	{
		enemy->setSpeed(horizontal, 0);

		//--set enemy shooting--
		if (enemy->dtSum >= enemy->shootingInterval)
		{
			if (enemy->side == left)
				enemy->bullets.push_back(new Bullet(enemy->getRect().left, enemy->getRect().top + 10, left));
			else if (enemy->side == right)
				enemy->bullets.push_back(new Bullet(enemy->getRect().left + enemy->getRect().width, enemy->getRect().top + 10, right));
		}
	}
}

void ActionGameState::objectsCollision(int direction)
{
	if (direction == horizontal)
	{
		//---check player's bullets and enemies collision---
		for (int i = 0; i < player.bullets.size(); i++)
		{
			for (int j = 0; j < enemies.size(); j++)
			{
				
				if (enemies[j]->getRect().intersects(player.bullets[i]->getRect()))
				{
					auto delBullet = player.bullets.begin() + i;
					auto delEnemy = enemies.begin() + j;
					
					enemies.erase(delEnemy);
					player.bullets.erase(delBullet);
					break;
				}
			}
			//check whether any player's bullets collide with borders 
			bulletBorderCollision(player.bullets[i]);
		}

		//check enemy's bullets collision with the map
		for (int enemyNum = 0; enemyNum < enemies.size(); enemyNum++)
		{
			for (int bulletNum = 0; bulletNum < enemies[enemyNum]->bullets.size(); bulletNum++)
			{
				//check whether any enemies' bullets collide with borders
				bulletBorderCollision(enemies[enemyNum]->bullets[bulletNum]);

				//---check player and enemies bullets collision---
				if (enemies[enemyNum]->bullets[bulletNum]->getRect().intersects(player.getRect()))
				{
					player.lifes--;
					player.setSpeed(vertical, -jumpSpeed);

					auto delBullet = enemies[enemyNum]->bullets.begin() + bulletNum;
					enemies[enemyNum]->bullets.erase(delBullet);
				}
			}
		}
	}
}

void ActionGameState::bulletBorderCollision(Bullet* bullet)
{
	for (int i = bullet->getRect().top / cellSize; i < (bullet->getRect().top + bullet->getRect().height) / cellSize; i++)
	{
		for (int j = bullet->getRect().left / cellSize; j < (bullet->getRect().left + bullet->getRect().width) / cellSize; j++)
		{
			if (map[i][j] == 'B')
			{
				bullet->isCollided = true;
			}
		}
	}
}

void ActionGameState::draw()
{
	game->window.setView(view);
	game->window.clear();
	game->window.draw(background);
	
	//---draw map----
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			if (map[i][j] == 'B')
			{
				drawBlock.setPosition(j * cellSize, i * cellSize);
				game->window.draw(drawBlock);
			}
			else if (map[i][j] == 'C')
			{
				coin.setPosition(j * cellSize, i * cellSize);
				game->window.draw(coin);
			}
			else
				continue;
		}
	}
	
	//draw player with his bullets
	game->window.draw(player);
	//draw enemies
	for (int i = 0; i < enemies.size(); i++)
	{
		game->window.draw(*enemies[i]);
	}

	//draw labels

	game->window.display();
}

ActionGameState::~ActionGameState()
{
	delete game;
}