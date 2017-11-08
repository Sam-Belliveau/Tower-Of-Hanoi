#include "Stand.h"

Stand::Stand(unsigned int amount, sf::Vector2f pos, sf::Vector2f size, Type type)
{
	construct(amount, pos, size, type);
}

Stand::Stand()
{
}

void Stand::construct(unsigned int amount, sf::Vector2f pos, sf::Vector2f size, Type type)
{
	this->max = amount;
	this->pos = pos;
	this->size = size;
	this->type = type;
	selected = false;

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
	if (type == Type::end)
	{
		stemColor = sf::Color(0, 255, 0);
	} else
	{
		stemColor = sf::Color(255, 255, 255);
	}

	stem[0].color = stemColor;
	stem[0].position = sf::Vector2f(pos.x + (size.x / 2 - size.x / stemMod), pos.y);

	stem[1].color = stemColor;
	stem[1].position = sf::Vector2f(pos.x + (size.x / 2 + size.x / stemMod), pos.y);

	stem[2].color = stemColor;
	stem[2].position = sf::Vector2f(pos.x + (size.x / 2 - size.x / stemMod), pos.y + size.y);

	stem[3].color = stemColor;
	stem[3].position = sf::Vector2f(pos.x + (size.x / 2 + size.x / stemMod), pos.y + size.y);

	window.draw(stem);

	base[0].color = baseColor;
	base[0].position = sf::Vector2f(pos.x, pos.y + (size.y - (size.y / baseMod)));

	base[1].color = baseColor;
	base[1].position = sf::Vector2f(pos.x + size.x, pos.y + (size.y - (size.y / baseMod)));

	base[2].color = baseColor;
	base[2].position = sf::Vector2f(pos.x, pos.y + size.y);

	base[3].color = baseColor;
	base[3].position = sf::Vector2f(pos.x + size.x, pos.y + size.y);

	window.draw(base);

	const float height = (size.y - (size.y / baseMod)) / ((float)max * heightMod);

	if (done)
	{
		diskColor = sf::Color::Green;
	} else
	{
		diskColor = sf::Color(255,0,0);
	}

	for (unsigned int i = 0; i < getAmount(); i++)
	{
		if (selected && i == getAmount() - 1)
		{
			minX = ((float)selectPos) - ((float)(stack[i] * size.x / 2) + 1) / ((float)max + 1);
			maxX = ((float)selectPos) + ((float)(stack[i] * size.x / 2) + 1) / ((float)max + 1);
			minY = (pos.y - height) / 2;
			maxY = (pos.y + height) / 2;
		} else
		{
			minX = ((size.x / 2) + pos.x) - (((float)stack[i] * size.x / 2) + 1) / ((float)max + 1);
			maxX = ((size.x / 2) + pos.x) + (((float)stack[i] * size.x / 2) + 1) / ((float)max + 1);
			minY = (pos.y + size.y) - ((i) * height) - (size.y / baseMod) - space;
			maxY = (pos.y + size.y) - ((i + 1) * height) - (size.y / baseMod);
		}

		temp[0].color = diskColor;
		temp[0].position = sf::Vector2f(minX, minY);

		temp[1].color = diskColor;
		temp[1].position = sf::Vector2f(minX, maxY);

		temp[2].color = diskColor;
		temp[2].position = sf::Vector2f(maxX, minY);

		temp[3].color = diskColor;
		temp[3].position = sf::Vector2f(maxX, maxY);

		window.draw(temp);
	}
}
