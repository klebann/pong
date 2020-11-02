//Pong Game by Jakub Kleban

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string.h>

int points1=0, points2=0;
bool pause = true, gameOver = false, prawy;

void reset(sf::RectangleShape& p1, sf::RectangleShape& p2, sf::CircleShape& ball, sf::Text& text1, sf::Text& text2, sf::Text& menu)
{
	p1.setPosition(30, 235);
	p2.setPosition(750, 235);
	ball.setPosition(400, 300);
	text1.setString("0");
	text2.setString("0");
	menu.setString("Wygral ");
	points1 = 0;
	points2 = 0;
	pause = true;
	gameOver = false;
}

int main()
{
	sf::RectangleShape p1({ 20,130 });
	p1.setFillColor(sf::Color::White);
	p1.setPosition( 30, 235);
	sf::RectangleShape p2({ 23,130 });
	p2.setFillColor(sf::Color::White);
	p2.setPosition(750, 235);

	sf::CircleShape ball(10, 50);
	ball.setFillColor(sf::Color::White);
	ball.setPosition(400, 300);
	sf::Vector2f speed(7.f, 7.f);

	sf::Font font;
	if (!font.loadFromFile("..\res\fonts.ttf"))
	{
		std::cout << "ERROR FONT!" << std::endl; // error...
	}

	sf::Text text1;
	// wybranie czcionki
	text1.setFont(font);
	// ustawienie stringa który ma byæ wyœwietlony
	text1.setString("0");
	// ustawienie wielkoœci czcionki
	text1.setCharacterSize(50); // w pikselach, nie punktach!
	// ustawienie koloru (standardowy kolor to bia³y)
	text1.setColor(sf::Color::White);
	// ustawienie stylu tekstu
	text1.setStyle(sf::Text::Bold);
	text1.setPosition(300, 10);

	sf::Text text2;
	// wybranie czcionki
	text2.setFont(font);
	// ustawienie stringa który ma byæ wyœwietlony
	text2.setString("0");
	// ustawienie wielkoœci czcionki
	text2.setCharacterSize(50); // w pikselach, nie punktach!
	// ustawienie koloru (standardowy kolor to bia³y)
	text2.setColor(sf::Color::White);
	// ustawienie stylu tekstu
	text2.setStyle(sf::Text::Bold);
	text2.setPosition(450, 10);

	sf::Text menu;
	// wybranie czcionki
	menu.setFont(font);
	// ustawienie stringa który ma byæ wyœwietlony
	menu.setString("Wygral ");
	// ustawienie wielkoœci czcionki
	menu.setCharacterSize(50); // w pikselach, nie punktach!
	// ustawienie koloru (standardowy kolor to bia³y)
	menu.setColor(sf::Color::White);
	// ustawienie stylu tekstu
	menu.setStyle(sf::Text::Bold);
	menu.setPosition(200, 250);

	sf::RenderWindow window(sf::VideoMode(800, 600), "Pong - Jakub Kleban SCI 2017", sf::Style::Close);
	window.setFramerateLimit(60);

	//Zarz¹dzanie czasem - zegar
	sf::Clock clock;

	//czas jaki mija od ostatniej aktualizacji
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	//czas trwania klatki
	sf::Time TimePerFrame = sf::seconds(1.0f / 60.0f);

	//Pêtla czasu rzeczywistego
	while (window.isOpen())
	{
		//obs³uga zdarzeñ
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
				pause = false;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
				reset(p1, p2, ball, text1, text2, menu);
		}
		if (!pause && !gameOver)
			timeSinceLastUpdate += clock.restart();//zliczamy czas...
		else
			clock.restart();

		while (timeSinceLastUpdate > TimePerFrame && !pause && !gameOver)
		{
			timeSinceLastUpdate -= TimePerFrame;

			if (ball.getPosition().x >= 757)
			{
				ball.setPosition(400, 300);
				std::string _str = std::to_string(++points2);
				text1.setString(_str);
				pause = true;
				p1.setPosition(30, 235);
				p2.setPosition(750, 235);
			}
			if (ball.getPosition().x <= 23)
			{
				ball.setPosition(400, 300);
				std::string _str = std::to_string(++points1);
				text2.setString(_str);
				pause = true;
				p1.setPosition(30, 235);
				p2.setPosition(750, 235);
			}

			if (points1 >= 10)
			{
				gameOver = true; prawy = true;
				if (prawy)
				{
					std::string tekst = "prawy gracz!";
					menu.setString(menu.getString() + tekst);
				}
				else
				{
					std::string tekst = "lewy gracz!";
					menu.setString(menu.getString() + tekst);
				}
			}
			if	(points2 >= 10)
			{
				gameOver = true; gameOver = true;
				if (prawy)
				{
					std::string tekst = "prawy gracz!";
					menu.setString(menu.getString() + tekst);
				}
				else
				{
					std::string tekst = "lewy gracz!";
					menu.setString(menu.getString() + tekst);
				}
			}


			if (ball.getPosition().y >= 600)
			{
				speed = sf::Vector2f(speed.x, -speed.y);
			}
			if (ball.getPosition().y < 0)
			{
				speed = sf::Vector2f(speed.x, -speed.y);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				p2.move(0, -8);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				p2.move(0, 8);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				p1.move(0, -8);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				p1.move(0, 8);
			}

			if (p1.getPosition().y <= 0)
			{
				p1.setPosition(30, 0);
			}
			if (p1.getPosition().y >= 470)
			{
				p1.setPosition(30, 470);
			}
			if (p2.getPosition().y <= 0)
			{
				p2.setPosition(750, 0);
			}
			if (p2.getPosition().y >= 470)
			{
				p2.setPosition(750, 470);
			}

			if (ball.getPosition().x >= p2.getPosition().x && ball.getPosition().y >= p2.getPosition().y && ball.getPosition().y <= p2.getPosition().y + 130)
			{
				speed = sf::Vector2f(-speed.x, speed.y);
			}
			if (ball.getPosition().x <= p1.getPosition().x && ball.getPosition().y >= p1.getPosition().y && ball.getPosition().y <= p1.getPosition().y + 130)
			{
				speed = sf::Vector2f(-speed.x, speed.y);
			}

			ball.move(speed);
		}

		window.clear(sf::Color::Black);
		window.draw(p1);
		window.draw(p2);
		window.draw(ball);
		window.draw(text1);
		window.draw(text2);
		
		if (gameOver)
		{
			window.clear(sf::Color::Black);
			window.draw(menu);
		}
		window.display();
	}

	return 0;
}