// main.cpp : Defines the entry point for the application.
#include "main.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <vector>

#include  "Hero.h"
#include  "Enemy.h"
#include "Rocket.h"

sf::Music bg_music;

sf::SoundBuffer fire_buffer;
sf::SoundBuffer hit_buffer;

sf::Sound fire_sound(fire_buffer);
sf::Sound hit_sound(hit_buffer);

sf::Vector2f view_size(1024, 768);
sf::VideoMode video_mode(view_size.x, view_size.y);

sf::RenderWindow window(video_mode, "Tiny Bazooka",
	sf::Style::Default);

void spawnEnemy();
void shoot();
bool checkCollision(sf::Sprite sprite1, sf::Sprite sprite2);
void reset();

sf::Texture sky_texture;
sf::Sprite sky_sprite;

sf::Texture bg_texture;
sf::Sprite bg_sprite;

Hero hero;

std::vector<Enemy*> enemies;
std::vector<Rocket*> rockets;

float currentTime;
float prevTime = 0.0f;

int score = 0;
bool game_over = true;

sf::Font heading_font;
sf::Text heading_text;

sf::Font score_font;
sf::Text score_text;

sf::Text tutorial_text;

void init()
{
	sky_texture.loadFromFile("Assets/graphics/sky.png");
	sky_sprite.setTexture(sky_texture);

	bg_texture.loadFromFile("Assets/graphics/bg.png");
	bg_sprite.setTexture(bg_texture);

	// Heading
	{
		heading_font.loadFromFile("Assets/fonts/SnackerComic.ttf");
		heading_text.setFont(heading_font);
		heading_text.setString("Tiny Bazooka");
		heading_text.setCharacterSize(84);
		heading_text.setFillColor(sf::Color::Red);
		const auto heading_bounds = heading_text.getLocalBounds();
		heading_text.setOrigin(heading_bounds.width / 2.0f,
			heading_bounds.height / 2.0f);
		heading_text.setPosition(sf::Vector2f(view_size.x * 0.5f,
			view_size.y * 0.10f));
	}

	// Score
	{
		score_font.loadFromFile("Assets/fonts/arial.ttf");
		score_text.setFont(score_font);
		score_text.setString("Score: 0");
		score_text.setCharacterSize(45);
		score_text.setFillColor(sf::Color::Red);

		const auto score_bounds = score_text.getLocalBounds();
		score_text.setOrigin(score_bounds.width / 2.0f,
			score_bounds.height / 2.0f);
		score_text.setPosition(sf::Vector2f(view_size.x * 0.5f, 
			view_size.y * 0.10f));
	}

	// Tutorial Text
	{
		tutorial_text.setFont(score_font);
		tutorial_text.setString("Press Down Arrow to Fire and Start Game, Up Arrow to Jump");
		tutorial_text.setCharacterSize(35);
		tutorial_text.setFillColor(sf::Color::Red);

		const auto tutorial_bounds = tutorial_text.getLocalBounds();
		tutorial_text.setOrigin(tutorial_bounds.width / 2.0f,
			tutorial_bounds.height / 2.0f);
		tutorial_text.setPosition(sf::Vector2f(view_size.x * 0.5f, view_size.y * 0.20f));
	}

	// Audio
	{
		bg_music.openFromFile("Assets/audio/bgMusic.ogg");
		bg_music.setLoop(true);
		bg_music.play();

		hit_buffer.loadFromFile("Assets/audio/hit.ogg");
		fire_buffer.loadFromFile("Assets/audio/fire.ogg");
	}

	hero.init("Assets/graphics/heroAnim.png", 4, 1.0f,
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

	fire_sound.play();
}

bool checkCollision(sf::Sprite sprite1, sf::Sprite sprite2)
{
	sf::FloatRect shape1 = sprite1.getGlobalBounds();
	sf::FloatRect shape2 = sprite2.getGlobalBounds();

	if (shape1.intersects(shape2))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void reset()
{
	score = 0;
	currentTime = 0.0f;
	prevTime = 0.0f;
	score_text.setString("Score: 0");

	for (auto& enemy : enemies)
	{
		delete(enemy);
	}
	for (auto& rocket : rockets)
	{
		delete rocket;
	}
	enemies.clear();
	rockets.clear();
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
				if (game_over)
				{
					game_over = false;
					reset();
				}
				else
				{
					shoot();
				}
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
			game_over = true;
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

	// Check collisions between rocket and enemies
	for (auto i = 0; i < rockets.size(); i++)
	{
		for (auto j = 0; j < enemies.size(); j++)
		{
			auto* rocket = rockets[i];
			auto* enemy = enemies[j];

			if (checkCollision(rocket->getSprite(), enemy->getSprite()))
			{
				hit_sound.play();
				// handle scoring
				{
					score++;
					auto final_score = "Score " + std::to_string(score);
					score_text.setString(final_score);
					const auto score_bounds = score_text.getLocalBounds();
					score_text.setOrigin(score_bounds.width / 2.0f,
						score_bounds.height / 2.0f);
					score_text.setPosition(sf::Vector2f(view_size.x * 0.5f,
						view_size.y * 0.10f));
				}
				
				
				rockets.erase(rockets.begin() + i);
				enemies.erase(enemies.begin() + j);

				delete(rocket);
				delete(enemy);
				printf(" rocket intersects enemy \n");
			}
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
	if (game_over)
	{
		window.draw(heading_text);
		window.draw(tutorial_text);
	}
	else
	{
		window.draw(score_text);
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
		if (!game_over)
		{
			update((dt.asSeconds()));
		}
		

		window.clear(sf::Color::Red);
		
		// Render Game Objects
		draw();
		window.display();
	}
	return 0;
}


