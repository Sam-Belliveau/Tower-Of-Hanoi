#include "SFML/Graphics.hpp"
#include "Type.h"
#include "Stand.h"

const unsigned int width = 1280;
const unsigned int height = 720;

const sf::Color front(224, 224, 224);
sf::Color back(32, 32, 32);

unsigned int amount = 3;
unsigned int max = 7;
unsigned int steps = 0;

Stand stands[3];

int calculateMin(int amount)
{
	return (1 << amount) - 1;
}

void reset()
{
	steps = 0;
	max = calculateMin(amount);
	stands[0] = Stand(amount, sf::Vector2f(64, 64), sf::Vector2f(342, 500), Type::start);
	stands[1] = Stand(amount, sf::Vector2f(470, 64), sf::Vector2f(342, 500), Type::misc);
	stands[2] = Stand(amount, sf::Vector2f(876, 64), sf::Vector2f(342, 500), Type::end);
}

void move(unsigned int start, unsigned int end)
{
	if (stands[end].addToTop(stands[start].getTop()))
	{
		stands[start].removeTop();
		steps++;
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(width, height), "Rings", sf::Style::Close);

	reset();

	window.setFramerateLimit(60);

	bool someBool = false;

	int start;

	sf::Font font;

	if (!font.loadFromFile("Consolas.ttf"))
	{
	}

	sf::Text score;

	score.setFont(font);
	score.setColor(front);
	score.setCharacterSize(64);
	score.setPosition(sf::Vector2f(64, 596));
	score.setStyle(sf::Text::Bold);
	score.setString("(Drop)	Steps: 0 / 7");

	reset();

	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				return 0;
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			int pos = sf::Mouse::getPosition(window).x;

			if (pos < width / 3)
			{
				if (someBool)
				{
					move(start, 0);
					someBool = false;
				} else
				{
					if (stands[0].getAmount() != 0)
					{
						start = 0;
						someBool = true;
					}
				}
			} else if (pos < (width / 3) * 2)
			{
				if (someBool)
				{
					move(start, 1);
					someBool = false;
				} else
				{
					if (stands[1].getAmount() != 0)
					{
						start = 1;
						someBool = true;
					}
				}
			} else
			{
				if (someBool)
				{
					move(start, 2);
					someBool = false;
				} else
				{
					if (stands[2].getAmount() != 0)
					{
						start = 2;
						someBool = true;
					}
				}
			}
			while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { reset(); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { 
			if (amount < 24)
			{
				amount++;
			}
			reset(); 
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			if (amount > 2)
			{
				amount--;
			}
			reset();
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {}
		}

		if (someBool)
		{
			back = sf::Color(32, 32, 40);
		} else
		{
			back = sf::Color(40, 32, 32);
		}

		window.clear(back);

		if (someBool)
		{
			score.setString("(Drop)	Steps: " + std::to_string(steps) + " / " + std::to_string(max));
		} else
		{
			score.setString("(Grab)	Steps: " + std::to_string(steps) + " / " + std::to_string(max));
		}

		stands[0].drawStack(window);
		stands[1].drawStack(window);
		stands[2].isDone();
		stands[2].drawStack(window);

		window.draw(score);
		window.display();
	}
}