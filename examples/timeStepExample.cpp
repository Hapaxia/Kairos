//////////////////////////////////////////////////////////////////////////////////////////////
//
//  Kairos - Timestep EXAMPLE
//
//  by Hapax (https://github.com/Hapaxia)
//
//
//    Controls:
//
//  Escape key          Quit
//  Arrow keys          Move
//  Space key           Toggle step value
//  1 key               Toggles interpolation (disables extrapolation)
//  2 key               Toggles extrapolation (disables interpolation)
//
//  Please note that this example makes use of C++11 features
//    and also requires the SFML library (http://www.sfml-dev.org)
//
//////////////////////////////////////////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>

#include <Kairos/Timestep.hpp>
#include <Kairos/FpsLite.hpp>

// linearInterpolation based on code in the Plinth library (https://github.com/Hapaxia/Plinth)
sf::Vector2f linearInterpolation(sf::Vector2f start, sf::Vector2f end, float alpha)
{
	return (start * (1 - alpha) + end * alpha);
}

int main()
{
	const std::string windowTitle{ "Timestep example" };
	sf::RenderWindow window(sf::VideoMode(800, 600), windowTitle, sf::Style::Default);
	window.setFramerateLimit(100); // max render rate is 100 fps (different to physics timestep)

	sf::CircleShape circle(50.f);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setFillColor(sf::Color(192, 128, 192));
	circle.setOutlineColor(sf::Color(64, 255, 192));
	circle.setOutlineThickness(-5.f);
	const float movementSpeed{ 250.f }; // pixels per second
	sf::Vector2f currentCirclePosition{ window.getSize() / 2u };
	sf::Vector2f previousCirclePosition = currentCirclePosition;

	bool interpolate{ false }, extrapolate{ false };

	kairos::FpsLite fps;

	kairos::Timestep timestep;
	timestep.setStep(1.0 / 5.0); // 'physics' timestep is one fifth of a second, or 5 frames per second.
	timestep.setMaxAccumulation(0.25); // set maximum time processed at once to a quarter of a second. if time passed is greater than this amount, the extra is discarded.
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Num1) // toggle interpolation
				{
					interpolate = !interpolate;
					extrapolate = false;
				}
				else if (event.key.code == sf::Keyboard::Num2) // toggle extrapolation
				{
					extrapolate = !extrapolate;
					interpolate = false;
				}
				else if (event.key.code == sf::Keyboard::Space) // toggle step value
				{
					if (timestep.getStep() > 1.0 / 6.0)
						timestep.setStep(1.0 / 60.0);
					else
						timestep.setStep(1.0 / 5.0);
				}
			}
		}

		fps.update();

		timestep.addFrame(); // add frame to timestep each cycle
		while (timestep.isUpdateRequired()) // this is true as long as there are unprocessed timesteps.
		{
			previousCirclePosition = currentCirclePosition;
			float dt{ timestep.getStepAsFloat() };

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) // move up
				currentCirclePosition.y -= movementSpeed * dt;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) // move down
				currentCirclePosition.y += movementSpeed * dt;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) // move left
				currentCirclePosition.x -= movementSpeed * dt;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) // move right
				currentCirclePosition.x += movementSpeed * dt;

			// keep circle inside the window
			if (currentCirclePosition.x < circle.getRadius())
				currentCirclePosition.x = circle.getRadius();
			else if (currentCirclePosition.x > window.getSize().x - circle.getRadius())
				currentCirclePosition.x = window.getSize().x - circle.getRadius();
			if (currentCirclePosition.y < circle.getRadius())
				currentCirclePosition.y = circle.getRadius();
			else if (currentCirclePosition.y > window.getSize().y - circle.getRadius())
				currentCirclePosition.y = window.getSize().y - circle.getRadius();
		}

		float interpolationAlpha{ timestep.getInterpolationAlphaAsFloat() }; // the interpolation alpha is how much the unprocessed time is of a step.
		if (extrapolate)
			// interpolates the current frame and the next frame predictively (extrapolation).
			// this is closer to the actual position but smooth only when movement is constant.
			// (interpolation between the previous frame and the current one is smoother but lags behind by a step)
			interpolationAlpha += 1.f;
		else if (!interpolate)
			interpolationAlpha = 1.f;
		circle.setPosition(linearInterpolation(previousCirclePosition, currentCirclePosition, interpolationAlpha));

		// shows information in the window title bar
		std::string infoTitle{ windowTitle };

		infoTitle += " || Fps: " + std::to_string(fps.getFps());
		infoTitle += " | Time passed: " + std::to_string(timestep.getTime());

		if (timestep.getStep() > 1.0 / 6.0)
			infoTitle += " || Timestep: 5 FPS";
		else
			infoTitle += " || Timestep: 60 FPS";
		if (interpolate)
			infoTitle += " | Interpolating";
		else if (extrapolate)
			infoTitle += " | Extrapolating";

		window.setTitle(infoTitle);

		window.clear();
		window.draw(circle);
		window.display();
	}

	return EXIT_SUCCESS;
}
