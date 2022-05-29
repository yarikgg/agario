#include <SFML/Graphics.hpp>

int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	const int gameWidth = 800;
	const int gameHeight = 600;
	float ballRadius = 10.f;
	int r = 0; int g = 0; int b = 0;
	int fx = 0; int fy = 0;
	int score = 0;
	int rad = 25;

	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "Agario",
		sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	// Create ball
	sf::CircleShape ball;
	ball.setRadius(rad);
	r = 0 + rand() % ((255 + 1) - 0); g = 0 + rand() % ((255 + 1) - 0); b = 0 + rand() % ((255 + 1) - 0);
	ball.setFillColor(sf::Color(r, g, b));
	ball.setPosition(400, 300);

	sf::CircleShape food;
	food.setRadius(15);
	r = 0 + rand() % ((255 + 1) - 0); g = 0 + rand() % ((255 + 1) - 0); b = 0 + rand() % ((255 + 1) - 0);
	food.setFillColor(sf::Color(r, g, b));
	fx = 0 + rand() % ((800 + 1) - 0); fy = 0 + rand() % ((600 + 1) - 0);
	food.setPosition(fx, fy);

	// Load the text font
	sf::Font font;
	if (!font.loadFromFile("resources/sansation.ttf"))
		return EXIT_FAILURE;

	sf::Text pauseMessage;
	pauseMessage.setFont(font);
	pauseMessage.setCharacterSize(20);
	pauseMessage.setFillColor(sf::Color::White);
	pauseMessage.setString("score:" + std::to_string(score));

	const float Speed = 2.f;

	bool isPlaying = false;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Quit
			if ((event.type == sf::Event::Closed) ||
				((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
			{
				window.close();
				break;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
			(ball.getPosition().y - 25 / 2 > 5.f))
		{
			ball.move(0.f, -Speed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
			(ball.getPosition().y + 25 / 2 < gameHeight - 5.f))
		{
			ball.move(0.f, Speed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
			(ball.getPosition().x > 0))
		{
			ball.move(-Speed, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
			(ball.getPosition().x < gameWidth))
		{
			ball.move(Speed, 0);
		}
		if (ball.getGlobalBounds().intersects(food.getGlobalBounds())) {
			rad += 5;
			ball.setRadius(rad);
			fx = 0 + rand() % ((800 + 1) - 0); fy = 0 + rand() % ((600 + 1) - 0);
			food.setPosition(fx, fy);
			r = 0 + rand() % ((255 + 1) - 0); g = 0 + rand() % ((255 + 1) - 0); b = 0 + rand() % ((255 + 1) - 0);
			ball.setFillColor(sf::Color(r, g, b));
			food.setFillColor(sf::Color(r, g, b));
			++score;
			pauseMessage.setString("score:" + std::to_string(score));
		}


		// Clear the window
		window.clear(sf::Color(0, 0, 0));

		window.draw(ball);
		window.draw(food);
		window.draw(pauseMessage);

		window.display();

	}
	return EXIT_SUCCESS;
}
