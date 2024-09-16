#include "ToolBar.h"

ToolBar::ToolBar(float x, float y, float squareSize)
{
	m_toolbar.setPosition(x, y);
	m_square.setSize(sf::Vector2f(squareSize, squareSize));

	// Calculate the gap between the squares
	float gap = squareSize / 4.0f;

	for (int i = 0; i < 6; i++) {
		m_square.setPosition(x + (squareSize + gap) * i, y);
		m_square.setFillColor(m_colors[i]);
		m_squares.push_back(m_square);
	}
	m_square.setSize(sf::Vector2f(Manager::instance().get_resetTexture().getSize().x, Manager::instance().get_resetTexture().getSize().y));

	// Create the reset button sprite
	m_resetButton.setTexture(Manager::instance().get_resetTexture());
	m_resetButton.setPosition(x + (squareSize + gap) * 6, y);

	//create the x sprites
	for (size_t i = 0; i < 2; i++)
	{
		m_notAvailableButton[i].setTexture(Manager::instance().get_notAvailableTexture());
		m_notAvailableButton[i].setPosition(1000, 1000);
	}
}
void ToolBar::draw(sf::RenderWindow& window)
{
	// Draw the squares in the toolbar
	for (int i = 0; i < 6; i++)
	{
		window.draw(m_squares[i]);
	}

	window.draw(m_resetButton);

	for (int i = 0; i < 2; ++i)
	{
		window.draw(m_notAvailableButton[i]);
	}
}

sf::Color ToolBar::getClickedColor(const sf::Vector2f& mousePosition)const
{
	for (std::size_t i = 0; i < m_squares.size(); ++i)
	{
		const sf::RectangleShape& button = m_squares[i];
		sf::FloatRect bounds = button.getGlobalBounds();

		if (bounds.contains(mousePosition))
		{
			return button.getFillColor();
		}
	}

	return sf::Color::White; // Default color if no color button is clicked
}

bool ToolBar::getClickedReset(const sf::Vector2f& mousePosition)const
{
	return m_resetButton.getGlobalBounds().contains(mousePosition);
}

void ToolBar::updateNotAvailable(std::vector<sf::Color> available)
{
	bool found;
	int index = 0;


	for (size_t i = 0; i < m_squares.size(); i++)
	{
		found = false;
		for (size_t j = 0; j < available.size(); j++)
		{
			if (m_squares[i].getFillColor() == available[j])
			{
				found = true;
				break;
			}
		}
		if (!found)
		{
			m_notAvailableButton[index].setPosition(m_squares[i].getPosition());
			index++;
		}
	}
}




