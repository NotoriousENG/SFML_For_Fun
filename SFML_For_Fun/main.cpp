// SFML_For_Fun.cpp : Defines the entry point for the application.
//
#include "main.h"
#include "SFML/Graphics.hpp"
#include <vector>

#include  "Hero.h"
#include  "Enemy.h"
#include "Rocket.h"

sf::Vector2f view_size(1024, 768);
sf::VideoMode video_mode(view_size.x, view_size.y);

sf::RenderWindow window(video_mode, "Hello SFMLGame !!!",
	sf::Style::Default);

void spawnEnemy();
void shoot();
// bool checkCollision(sf::Sprite sprite1, sf::Sprite sprite2);

sf::Texture sky_texture;
sf::Sprite sky_sprite;

sf::Texture bg_texture;
sf::Sprite bg_sprite;

Hero hero;

std::vector<Enemy*> enemies;
std::vector<Rocket*> rockets;

float currentTime;
float prevTime = 0.0f;

void init()
{
	sky_texture.loadFromFile("Assets/graphics/sky.png");
	sky_sprite.setTexture(sky_texture);

	bg_texture.loadFromFile("Assets/graphics/bg.png");
	bg_sprite.setTexture(bg_texture);

	hero.init("Assets/graphics/hero.png", 
		sf::Vector2f(view_size.x * 0.25f, 
			view_size.y * 0.5f), 200);

	srand(static_cast<int>(time(0)));
}

void spawnEnemy()
{
	int randLoc = rand() % 3;
	sf::Vector2f enemyPos;
	float speed;

	switch (randLoc)
	{
	case 0:
		enemyPos = sf::Vector2f(view_size.x, view_size.y * 0.75);
		speed = -400;
		break;

	case 1:
		enemyPos = sf::Vector2f(view_size.x, view_size.y * 0.60f);
		speed = -550;
		break;

	case 2:
		enemyPos = sf::Vector2f(view_size.x, view_size.y * 0.40f);
		speed = -650;
		break;

	default:
		printf("incorrect y value \n");
		return;
	}

	// ALLOCATE ENEMY
	auto* enemy = new Enemy();
	enemy->init("Assets/graphics/enemy.png", enemyPos, speed);

	enemies.push_back(enemy);
}

void shoot()
{
	auto* rocket = new Rocket();

	rocket->init("Assets/graphics/rocket.png",
		hero.getSprite().getPosition(), 400.0f);

	rockets.push_back(rocket);
}

void updateInput()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Up)
			{
				hero.jump(750.0f);
			}
			if (event.key.code == sf::Keyboard::Down)
			{
				shoot();
			}
		}
		if (event.key.code == sf::Keyboard::Escape || 
				event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}

void update(float dt)
{
	hero.update(dt);

	currentTime += dt;
	// Spawn enemies
	if (currentTime >= prevTime + 1.125f)
	{
		spawnEnemy();
		prevTime = currentTime;
	}

	// Update Enemies
	for (auto i = 0; i < enemies.size(); i++)
	{
		auto* enemy = enemies[i];
		enemy->update(dt);

		if (enemy->getSprite().getPosition().x < 0)
		{
			enemies.erase(enemies.begin() + i);
			delete(enemy); // FREE ENEMY
		}
	}
	// Update Rockets
	for (auto i = 0; i < rockets.size(); i++)
	{
		auto* rocket = rockets[i];

		rocket->update(dt);

		if (rocket->getSprite().getPosition().x > view_size.x)
		{
			rockets.erase(rockets.begin() + i);
			delete(rocket); // FREE ROCKET
		}
	}
}

void draw()
{
	window.draw(sky_sprite);
	window.draw(bg_sprite);
	window.draw(hero.getSprite());

	for (auto& enemy : enemies)
	{
		window.draw(enemy->getSprite());
	}

	for (auto& rocket : rockets)
	{
		window.draw(rocket->getSprite());
	}
}

int main()
{
	// Initialize timer
	sf::Clock clock;
	// Initialize Game Objects
	init();
	
	while (window.isOpen())
	{
		// Update Input
		updateInput();
		
		// Update Game Objects in the Scene
		sf::Time dt = clock.restart();
		// 60 fps
		update((dt.asSeconds()));

		window.clear(sf::Color::Red);
		
		// Render Game Objects
		draw();
		window.display();
	}
	return 0;
}
