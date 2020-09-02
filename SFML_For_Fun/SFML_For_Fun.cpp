// SFML_For_Fun.cpp : Defines the entry point for the application.
//
#include "SFML_For_Fun.h"
#include "SFML/Graphics.hpp"

sf::Vector2f view_size(1024, 768);
sf::VideoMode video_mode(view_size.x, view_size.y);

sf::RenderWindow window(video_mode, "Hello SFMLGame !!!",
	sf::Style::Default);

sf::Texture sky_texture;
sf::Sprite sky_sprite;

sf::Texture bg_texture;
sf::Sprite bg_sprite;

sf::Texture hero_texture;
sf::Sprite hero_sprite;

sf::Vector2f player_position;
bool player_moving = false;

using namespace std;

void init()
{
	sky_texture.loadFromFile("Assets/graphics/sky.png");
	sky_sprite.setTexture(sky_texture);

	bg_texture.loadFromFile("Assets/graphics/bg.png");
	bg_sprite.setTexture(bg_texture);

	hero_texture.loadFromFile("Assets/graphics/hero.png");
	hero_sprite.setTexture(hero_texture);
	hero_sprite.setPosition(sf::Vector2f(view_size.x / 2, view_size.y / 2));
	hero_sprite.setOrigin(hero_texture.getSize().x / 2.0f, hero_texture.getSize().y / 2.0f);
}

void draw()
{
	window.draw(sky_sprite);
	window.draw(bg_sprite);
	window.draw(hero_sprite);
}

void updateInput()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Right)
			{
				player_moving = true;
			}
		}
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Right)
			{
				player_moving = false;
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
	if (player_moving)
	{
		hero_sprite.move(50.0f * dt, 0);
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
