#pragma once
#include "Type.h"
#include "SFML/Graphics.hpp"
class Stand
{
public:
	Stand(unsigned int amount, sf::Vector2f pos, sf::Vector2f size, Type type);
	Stand();

	void construct(unsigned int amount, sf::Vector2f pos, sf::Vector2f size, Type type);

	// Data relating to other disks
	Type type = Type::misc;
	sf::Vector2f pos, size;

	// Vector Length
	unsigned int getAmount();

	// Checking To See If Done
	bool done = false;
	bool isDone();

	// Moving Stuff
	unsigned int getTop();
	bool addToTop(unsigned int i);
	void removeTop();

	// Drawing
	void drawStack(sf::RenderWindow& window);

	// Selecting Discs
	bool selected = false;
	int selectPos = 0;

private:
	// Disc Data
	unsigned int max;
	std::vector<unsigned int> stack;

	// Re-used Drawing Variables
	const sf::Color baseColor = sf::Color(255, 255, 255);
	const float baseMod = 12;
	const float space = 4;
	const float heightMod = 1.375;
	const float stemMod = 64;

	float minX;
	float maxX;
	float minY;
	float maxY;

	sf::Color diskColor = sf::Color(255, 0, 0);
	sf::VertexArray temp = sf::VertexArray(sf::TrianglesStrip, 4);
	sf::VertexArray base = sf::VertexArray(sf::TrianglesStrip, 4);
	sf::VertexArray stem = sf::VertexArray(sf::TrianglesStrip, 4);
	sf::Color stemColor = sf::Color(255, 255, 255);

};

