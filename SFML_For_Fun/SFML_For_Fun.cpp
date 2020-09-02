// SFML_For_Fun.cpp : Defines the entry point for the application.
//
#include "SFML_For_Fun.h"
#include "SFML/Graphics.hpp"
#include  "Hero.h"

sf::Vector2f view_size(1024, 768);
sf::VideoMode video_mode(view_size.x, view_size.y);

sf::RenderWindow window(video_mode, "Hello SFMLGame !!!",
	sf::Style::Default);

sf::Texture sky_texture;
sf::Sprite sky_sprite;

sf::Texture bg_texture;
sf::Sprite bg_sprite;

Hero hero;

void init()
{
	sky_texture.loadFromFile("Assets/graphics/sky.png");
	sky_sprite.setTexture(sky_texture);

	bg_texture.loadFromFile("Assets/graphics/bg.png");
	bg_sprite.setTexture(bg_texture);

	hero.init("Assets/graphics/hero.png", 
		sf::Vector2f(view_size.x * 0.25f, 
			view_size.y * 0.5f), 200);
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
}

void draw()
{
	window.draw(sky_sprite);
	window.draw(bg_sprite);
	window.draw(hero.getSprite());
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
