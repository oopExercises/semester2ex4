#pragma once 
#include "Manager.h"
#include <ctime>
#include <list>


class Hexagon
{
private:
	sf::CircleShape m_hexagon;;
	bool m_visited;
	std::pair<int, int> m_coordinate;
public:
	Hexagon(const sf::Vector2f&);

	void setCoordinates(int, int);
	std::pair<int, int> getCoordinates()const;

	sf::CircleShape getShape()const;

	void setColor(sf::Color);
	void setOutlineColor(sf::Color);
	sf::Color getColor()const;

	void setVisited(bool v);
	bool getVisited()const;
};