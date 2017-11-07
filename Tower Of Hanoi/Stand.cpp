#include "Stand.h"

Stand::Stand(unsigned int amount, sf::Vector2f pos, sf::Vector2f size, Type type)
{
	this->max = amount;
	this->pos = pos;
	this->size = size;
	this->type = type;

	stack.clear();
	stack.resize(0);

	if (type == Type::start)
	{
		for (unsigned int i = amount; i > 0; i--)
		{
			addToTop(i);
		}
	}
}

Stand::Stand()
{
}

unsigned int Stand::getAmount()
{
	return stack.size();
}

bool Stand::isDone()
{
	if (type == Type::end)
	{
		if (getAmount() == max)
		{
			done = true;
			return true;
		}
	}
	done = false;
	return false;
}

bool Stand::addToTop(unsigned int i)
{
	if (getAmount() < max)
	{
		if (getAmount() == 0)
		{
			stack.push_back(i);
			return true;
		} else if (stack.back() > i)
		{
			stack.push_back(i);
			return true;
		}
	}
	return false;
}

unsigned int Stand::getTop()
{
	if (getAmount() != 0)
	{
		return stack.back();
	} 
	return max + 1;
}

void Stand::removeTop()
{
	stack.pop_back();
}

void Stand::drawStack(sf::RenderWindow & window)
{
	const int baseMod = 16;
	const int stemMod = 64;
	const int space = 5;
	const float heightMod = 1.5;

	sf::VertexArray stem(sf::TrianglesStrip, 4);
	stem[0].color = sf::Color::White;
	stem[0].position = sf::Vector2f(pos.x + (size.x / 2 - size.x / stemMod), pos.y);

	stem[1].color = sf::Color::White;
	stem[1].position = sf::Vector2f(pos.x + (size.x / 2 + size.x / stemMod), pos.y);

	stem[2].color = sf::Color::White;
	stem[2].position = sf::Vector2f(pos.x + (size.x / 2 - size.x / stemMod), pos.y + size.y);

	stem[3].color = sf::Color::White;
	stem[3].position = sf::Vector2f(pos.x + (size.x / 2 + size.x / stemMod), pos.y + size.y);

	window.draw(stem);

	sf::Color baseColor = sf::Color::White;

	if (type == Type::start)
	{
		baseColor = sf::Color::Magenta;
	} else if (type == Type::end)
	{
		baseColor = sf::Color::Cyan;
	}

	sf::VertexArray base(sf::TrianglesStrip, 4);
	base[0].color = baseColor;
	base[0].position = sf::Vector2f(pos.x, pos.y + (size.y - (size.y / baseMod)));

	base[1].color = baseColor;
	base[1].position = sf::Vector2f(pos.x + size.x, pos.y + (size.y - (size.y / baseMod)));

	base[2].color = baseColor;
	base[2].position = sf::Vector2f(pos.x, pos.y + size.y);

	base[3].color = baseColor;
	base[3].position = sf::Vector2f(pos.x + size.x, pos.y + size.y);

	window.draw(base);

	const int height = (((size.y + pos.y) - ((size.y + pos.y) / baseMod)) - space * max) / (int)((float)max * heightMod);

	sf::Color color = sf::Color::Red;

	if (done)
	{
		color = sf::Color::Green;
	}

	for (unsigned int i = 0; i < getAmount(); i++)
	{
		const int minX = ((size.x / 2) + pos.x) - ((stack[i] * size.x / 2) / (max + 1));
		const int maxX = ((size.x / 2) + pos.x) + ((stack[i] * size.x / 2) / (max + 1));

		const int minY = ((size.y + pos.y) - ((size.y) / baseMod)) - ((i) * height + i * space);
		const int maxY = ((size.y + pos.y) - ((size.y) / baseMod)) - ((i + 1) * height + i * space);

		sf::VertexArray temp(sf::TrianglesStrip, 4);
		temp[0].color = color;
		temp[0].position = sf::Vector2f(minX, minY);

		temp[1].color = color;
		temp[1].position = sf::Vector2f(minX, maxY);

		temp[2].color = color;
		temp[2].position = sf::Vector2f(maxX, minY);

		temp[3].color = color;
		temp[3].position = sf::Vector2f(maxX, maxY);

		window.draw(temp);
	}
}
