#include "SFML/Graphics.hpp"
#include "Type.h"
#include "Stand.h"

const unsigned int width = 1200;
const unsigned int height = 675;

const sf::Color front(255, 255, 255);
const sf::Color back(48, 48, 48);

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
	stands[0].construct(amount, sf::Vector2f(75, 150), sf::Vector2f(300, 400), Type::start);
	stands[1].construct(amount, sf::Vector2f(450, 150), sf::Vector2f(300, 400), Type::misc);
	stands[2].construct(amount, sf::Vector2f(825, 150), sf::Vector2f(300, 400), Type::end);
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
	printf("Controls:\n");
	printf("	Add More Discs - (Up)\n\n");

	printf("	Remove Discs - (Down)\n\n");

	printf("	Reset - (Space)\n\n");

	printf("	Move Discs - (Mouse)\n\n");

	sf::ContextSettings set;
	set.antialiasingLevel = 16;

	sf::RenderWindow window(sf::VideoMode(width, height), "Towers of Hanoi", sf::Style::Close, set);

	reset();

	window.setFramerateLimit(60);

	bool someBool = false;

	int start = 0;

	sf::Font font;

	if (!font.loadFromFile("Consolas.ttf"))
	{
	}

	sf::Text score;

	score.setFont(font);
	score.setColor(front);
	score.setCharacterSize(60);
	score.setPosition(sf::Vector2f(75, 575));
	score.setStyle(sf::Text::Bold);
	score.setString("Steps: 0 / 7");

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

		if (window.hasFocus())
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				int pos = sf::Mouse::getPosition(window).x;

				if (pos < width / 3)
				{
					stands[start].selectPos = (width / 6);

					if (someBool)
					{
						move(start, 0);
						stands[start].selected = false;
						someBool = false;
					} else
					{
						if (stands[0].getAmount() != 0)
						{
							start = 0;
							stands[start].selected = true;
							someBool = true;
						}
					}
				} else if (pos < (width / 3) * 2)
				{
					stands[start].selectPos = (width / 2);

					if (someBool)
					{
						move(start, 1);
						stands[start].selected = false;
						someBool = false;
					} else
					{
						if (stands[1].getAmount() != 0)
						{
							start = 1;
							stands[start].selected = true;
							someBool = true;
						}
					}
				} else
				{
					stands[start].selectPos = (width / 6) * 5;

					if (someBool)
					{
						move(start, 2);
						stands[start].selected = false;
						someBool = false;
					} else
					{
						if (stands[2].getAmount() != 0)
						{
							start = 2;
							stands[start].selected = true;
							someBool = true;
						}
					}
				}
				while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { reset(); }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if (amount < 24)
				{
					amount++;
				}
				reset();
				while (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if (amount > 2)
				{
					amount--;
				}
				reset();
				while (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {}
			}
		}
		if (someBool)
		{
			if (sf::Mouse::getPosition(window).x < width / 3)
			{
				stands[start].selectPos = (375 * 1) - 150;
			} else if (sf::Mouse::getPosition(window).x < (width / 3) * 2)
			{
				stands[start].selectPos = (375 * 2) - 150;
			} else
			{
				stands[start].selectPos = (375 * 3) - 150;
			}
		}

		window.clear(back);

		if (amount < 10)
		{
			score.setString("(" + std::to_string(amount) + ")	 Steps: " + std::to_string(steps) + " / " + std::to_string(max));
		} else
		{
			score.setString("(" + std::to_string(amount) + ")	Steps: " + std::to_string(steps) + " / " + std::to_string(max));
		}

		stands[0].drawStack(window);
		stands[1].drawStack(window);
		stands[2].isDone();
		stands[2].drawStack(window);

		window.draw(score);
		window.display();
	}
}