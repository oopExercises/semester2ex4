#include "Hexagon.h"

Hexagon::Hexagon(const sf::Vector2f& position) : m_visited(false)
{
	m_hexagon = sf::CircleShape(HEXAGON_RADIUS, HEXAGON_SIDES_NUM);
	m_hexagon.setPosition(position);
	sf::Color color = COLORS[rand() % 6];
	m_hexagon.setFillColor(color);
	m_hexagon.setOutlineColor(sf::Color::Black);
	m_hexagon.setOutlineThickness(1.0f);
}


void Hexagon::setCoordinates(int row, int col)
{
	m_coordinate.first = row;
	m_coordinate.second = col;
}

std::pair<int, int> Hexagon::getCoordinates()const
{
	return m_coordinate;
}

sf::CircleShape Hexagon::getShape() const
{
	return m_hexagon;
}

void Hexagon::setColor(sf::Color color)
{
	m_hexagon.setFillColor(color);

}

void Hexagon::setOutlineColor(sf::Color color)
{
	m_hexagon.setOutlineColor(color);
}

sf::Color Hexagon::getColor()const
{
	return m_hexagon.getFillColor();
}

void Hexagon::setVisited(bool v)
{
	m_visited = v;
}

bool Hexagon::getVisited()const
{
	return m_visited;
}
