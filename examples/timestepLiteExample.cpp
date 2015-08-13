//////////////////////////////////////////////////////////////////////////////////////////////
//
//  Kairos - Timestep Lite EXAMPLE
//
//  by Hapax (https://github.com/Hapaxia)
//
//
//    Controls:
//
//  Escape key          Quit
//  Arrow keys          Move
//  Space key           Toggle step value
//
//  Please note that this example makes use of C++11 features
//    and also requires the SFML library (http://www.sfml-dev.org)
//
//////////////////////////////////////////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>

#include <Kairos/TimestepLite.hpp>
#include <Kairos/Stopwatch.hpp>

int main()
{
	const std::string windowTitle{ "TimestepLite example" };
	sf::RenderWindow window(sf::VideoMode(800, 600), windowTitle, sf::Style::Default);
	window.setFramerateLimit(100); // max render rate is 100 fps (different to physics timestep)

	sf::CircleShape circle(50.f);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setFillColor(sf::Color(192, 128, 192));
	circle.setOutlineColor(sf::Color(64, 255, 192));
	circle.setOutlineThickness(-5.f);
	const float movementSpeed{ 250.f }; // pixels per second
	sf::Vector2f circlePosition{ window.getSize() / 2u };

	kairos::Stopwatch clock;
	kairos::TimestepLite timestep;
	timestep.setStep(1.0 / 5.0); // 'physics' timestep is one fifth of a second, or 5 frames per second.
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					if (timestep.getStep() > 1.0 / 6.0)
						timestep.setStep(1.0 / 60.0);
					else
						timestep.setStep(1.0 / 5.0);
				}
			}
		}

		timestep.update(clock.restart().asSeconds()); // add frame time each cycle
		while (timestep.isTimeToIntegrate()) // this is true as long as there are unprocessed timesteps.
		{
			float dt{ static_cast<float>(timestep.getStep()) };

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				circlePosition.y -= movementSpeed * dt;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				circlePosition.y += movementSpeed * dt;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				circlePosition.x -= movementSpeed * dt;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				circlePosition.x += movementSpeed * dt;

			// keep circle inside the window
			if (circlePosition.x < circle.getRadius())
				circlePosition.x = circle.getRadius();
			else if (circlePosition.x > window.getSize().x - circle.getRadius())
				circlePosition.x = window.getSize().x - circle.getRadius();
			if (circlePosition.y < circle.getRadius())
				circlePosition.y = circle.getRadius();
			else if (circlePosition.y > window.getSize().y - circle.getRadius())
				circlePosition.y = window.getSize().y - circle.getRadius();
		}
		circle.setPosition(circlePosition);

		// shows information in the window title bar
		std::string infoTitle{ windowTitle };
		if (timestep.getStep() > 1.0 / 6.0)
			infoTitle += " | Timestep: 5 FPS";
		else
			infoTitle += " | Timestep: 60 FPS";
		window.setTitle(infoTitle);

		window.clear();
		window.draw(circle);
		window.display();
	}

	return EXIT_SUCCESS;
}
