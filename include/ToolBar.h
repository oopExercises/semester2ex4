#pragma once
#include "Manager.h"

class ToolBar
{
private:

	sf::RectangleShape m_square;
	std::vector<sf::RectangleShape> m_squares;
	sf::Color m_colors[6] = { sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta, sf::Color::Cyan };
	sf::RectangleShape m_toolbar;

	sf::Sprite m_resetButton;
	sf::Sprite m_notAvailableButton[2];
	
public:
	ToolBar() =  default;
	ToolBar(float, float,float);
	void draw(sf::RenderWindow&);
	sf::Color getClickedColor(const sf::Vector2f& mousePosition)const;
	bool getClickedReset(const sf::Vector2f& mousePosition)const;
	void updateNotAvailable(std::vector<sf::Color> available);
};