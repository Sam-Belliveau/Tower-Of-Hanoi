#pragma once
#include "Type.h"
#include "SFML/Graphics.hpp"
class Stand
{
public:
	Stand(unsigned int amount, sf::Vector2f pos, sf::Vector2f size, Type type);
	Stand();

	Type type = Type::misc;
	std::vector<unsigned int> stack;
	sf::Vector2f pos, size;
	bool done = false;

	unsigned int max;

	unsigned int getAmount();

	bool isDone();

	unsigned int getTop();
	bool addToTop(unsigned int i);
	void removeTop();

	void drawStack(sf::RenderWindow& window);

};

