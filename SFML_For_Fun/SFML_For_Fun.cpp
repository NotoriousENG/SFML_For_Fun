// SFML_For_Fun.cpp : Defines the entry point for the application.
//

#include "SFML_For_Fun.h"
#include "SFML/Graphics.hpp"

sf::Vector2f view_size(1024, 768);
sf::VideoMode video_mode(view_size.x, view_size.y);

sf::RenderWindow window(video_mode, "Hello SFMLGame !!!",
	sf::Style::Default);

using namespace std;

int main()
{
	// Initialize Game Objects
	while (window.isOpen())
	{
		// Handle Keyboard Events
		// Update Game Objects in the Scene
		// Render Game Objects
	}
	return 0;
}
