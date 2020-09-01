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

	sf::RectangleShape rect(sf::Vector2f(500.0f, 300.0f));
	rect.setFillColor(sf::Color::Yellow);
	rect.setPosition(view_size.x / 2, view_size.y / 2);
	rect.setOrigin(sf::Vector2f(rect.getSize().x / 2,
		rect.getSize().y / 2));

	sf::CircleShape circle(100);
	circle.setFillColor(sf::Color::Green);
	circle.setPosition(view_size.x / 2, view_size.y / 2);
	circle.setOrigin(sf::Vector2f(circle.getRadius(), circle.getRadius()));

	sf::ConvexShape triangle;
	triangle.setPointCount(3);
	triangle.setPoint(0, sf::Vector2f(-100, 0));
	triangle.setPoint(1, sf::Vector2f(0, -100));
	triangle.setPoint(2, sf::Vector2f(100, 0));
	triangle.setFillColor(sf::Color(128, 0, 128, 255));
	triangle.setPosition(view_size.x / 2, view_size.y / 2);

	
	while (window.isOpen())
	{
		// Handle Keyboard Events
		// Update Game Objects in the Scene

		window.clear(sf::Color::Red);
		// Render Game Objects
		window.draw(rect);
		window.draw(circle);
		window.draw(triangle);
		window.display();
	}
	return 0;
}
