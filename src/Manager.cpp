#include "Manager.h"
#include "Hexagon.h"


Manager::Manager()
{
	if (!m_resetTexture.loadFromFile("reset.png"))
	{
		std::cout << " error in the texture" << std::endl;
	}
	if (!m_notAvailableTexture.loadFromFile("notAvailable.png"))
	{
		std::cout << " error in the texture" << std::endl;
	}

	if (!m_font.loadFromFile("Raleway.ttf"))
	{
		std::cout << " error in the font" << std::endl;
	}

}
Manager& Manager::instance()
{
	static Manager instance;
	return instance;
}

const sf::Texture& Manager::get_resetTexture() const
{
	return m_resetTexture;
}

const sf::Texture& Manager::get_notAvailableTexture() const
{
	return m_notAvailableTexture;
}

const sf::Font& Manager::getFont() const
{
	return m_font;
}
