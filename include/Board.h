#pragma once
#include "Manager.h"
#include "Hexagon.h"
#include "ToolBar.h"
#include "Bfs.h"

class Board
{
private:
	std::vector<std::vector<Hexagon>> m_grid;
	std::vector<Hexagon> m_playersHexagons;
	std::vector<Hexagon> m_computersHexagons;
	std::map<std::string, sf::Text> m_texts;
	std::vector<sf::Color> m_availableColors;

	Bfs m_bfs;

	sf::Color m_playerColor;
	sf::Color m_computerColor;

	void buildGrid();
	ToolBar m_toolBar;

	float m_playerPoints;
	float m_computerPoints;
	bool m_playerWon;
	

public:
	Board(sf::RenderWindow&);
	~Board() {};

	void makeMessages();
	void drawScreen(sf::RenderWindow&);

	ToolBar_Buttons press(const sf::Vector2f& position);
	void moveComputer(Level);
	void setCurrentColor(std::vector<Hexagon>& ,sf::Color);
	bool checkWonOrLost(sf::RenderWindow&);
	bool drawFinishScreen(sf::RenderWindow&, sf::Event event);
	void fillAvailableColors();
};