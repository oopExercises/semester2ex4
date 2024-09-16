#pragma once
#include "Board.h"
#include <Controller.h>

class Controller
{
private:
	sf::RenderWindow m_render_window;

	Level m_level;

	ToolBar_Buttons m_clickedButton;

public:
	Controller();
	void run();
	int choseLevel(sf::RenderWindow& window, sf::Event& event);
};