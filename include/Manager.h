#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include <vector>
#include <iostream>
#include <string>

class Manager
{
private:
	sf::Texture m_resetTexture;
	sf::Texture m_notAvailableTexture;
	sf::Font m_font;

	Manager();
	Manager(const Manager&) = delete;
	

public :
	static Manager& instance();
	~Manager() = default;

	const sf::Texture& get_resetTexture() const;
	const sf::Texture& get_notAvailableTexture() const;
	const sf::Font& getFont() const;

};