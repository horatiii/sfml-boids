#ifndef MAIN_
#define MAIN_
#include <SFML/Graphics.hpp>
#include "engine.hpp"
#include "config.hpp"
#include "boid.hpp"

/*
 *main function contains main loop
 *
 */
int main()
{
	sf::Text text;
	sf::Font font;
	if(!font.loadFromFile("../fonts/Arvo-Regular.ttf"))
	{
		std::cout<<"no such font\n";
		return -1;
	}

	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White); 
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML boids",sf::Style::None);
	window.setFramerateLimit(FRAMERATE);
	Engine e(QUANTITY);


	for(Boid &b: e.boids)
	{
		b.cs.setFillColor(b.color);
		b.cs.setPosition(b.position[0],b.position[1]);
	}

	//main loop starts here
	while (window.isOpen())
	{
		text.setString("framerate: "+ std::to_string(FRAMERATE)
								+  "\nviewDist: "+ std::to_string(e.viewDist)
								+  "\nspeedLim: "+ std::to_string(e.vLimit)
				);


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		e.update();

		for(Boid &b: e.boids) b.cs.setPosition(b.position[0],b.position[1]); 

		window.clear();

		for(Boid &b: e.boids) window.draw(b.cs);


		window.draw(text);
		window.display();
	}

	return 0;
}
#endif
