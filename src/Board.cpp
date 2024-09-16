#pragma once
#include "Board.h"

void Board::buildGrid()
{
	float xPosition = 100;
	float yPosition = 100;

	for (int row = 0; row < HEIGHT; row++)
	{
		auto temp = std::vector<Hexagon>();

		for (int col = 0; col < WIDTH; col++)
		{
			auto position = sf::Vector2f(xPosition, yPosition);
			Hexagon tempHex(position);
			auto& hexagon = tempHex;

			hexagon.setCoordinates(row, col);
			temp.push_back(hexagon);
			xPosition += sqrt(3) * (HEXAGON_RADIUS + 1);
		}
		m_grid.push_back(temp);
		if (row % 2 != 1)
			xPosition = 100 + sqrt(3) / 2 * (HEXAGON_RADIUS + 1);
		else
			xPosition = 100;
		yPosition = yPosition + ((3.0f / 4.0f) * ((HEXAGON_RADIUS + 1) * 2));
	}
}

void Board::makeMessages()
{
	std::string playerPointsString = std::to_string(m_playerPoints);
	std::string computerPointsString = std::to_string(m_computerPoints);

	auto& font = Manager::instance().getFont();

	sf::Text winMessage;
	winMessage.setFont(font);
	winMessage.setString("CONGRATS, YOU WON");
	winMessage.setCharacterSize(30);
	winMessage.setFillColor(sf::Color::Cyan);
	winMessage.setPosition(220, 350);

	sf::Text loseMessage;
	loseMessage.setFont(font);
	loseMessage.setString("YOU LOST, TRY AGAIN");
	loseMessage.setCharacterSize(30);
	loseMessage.setFillColor(sf::Color::Cyan);
	loseMessage.setPosition(220, 350);

	sf::Text playAgain;
	playAgain.setFont(font);
	playAgain.setString("             if you want to play again \n Please press the left button on the mouse");
	playAgain.setCharacterSize(30);
	playAgain.setFillColor(sf::Color::White);
	playAgain.setPosition(120, 450);

	sf::Text playerPoints;
	playerPoints.setFont(font);
	playerPoints.setString("PLAYER: " + playerPointsString);
	playerPoints.setCharacterSize(25);
	playerPoints.setFillColor(sf::Color::Black);
	playerPoints.setPosition(100, 710);

	sf::Text computerPoints;
	computerPoints.setFont(font);
	computerPoints.setString("COMPUTER: " + computerPointsString);
	computerPoints.setCharacterSize(25);
	computerPoints.setFillColor(sf::Color::Black);
	computerPoints.setPosition(500, 710);

	m_texts[WIN] = winMessage;
	m_texts[LOSE] = loseMessage;
	m_texts[TRY_AGAIN] = playAgain;
	m_texts[PLAYER] = playerPoints;
	m_texts[COMPUTER] = computerPoints;

}

Board::Board(sf::RenderWindow& window)
{
	buildGrid();
	m_playersHexagons.push_back(m_grid[HEIGHT - 1][0]);
	m_computersHexagons.push_back(m_grid[0][HEIGHT - 1]);
	m_grid[HEIGHT - 1][0].setVisited(true);
	m_grid[HEIGHT - 1][0].setOutlineColor(sf::Color::White);
	m_grid[0][HEIGHT - 1].setOutlineColor(sf::Color(120, 120, 120));
	m_computerPoints = 1 / NUM_OF_HEXAGONS;
	m_playerPoints = 1 / NUM_OF_HEXAGONS;
	makeMessages();
	m_playerColor = m_grid[HEIGHT - 1][0].getColor();
	m_computerColor = m_grid[0][HEIGHT - 1].getColor();
	m_toolBar = ToolBar(200, 660, 32);
	m_playerWon = false;
}

void Board::drawScreen(sf::RenderWindow& window)
{
	for (auto& row : m_grid)
		for (auto& hexagon : row)
			window.draw(hexagon.getShape());

	m_toolBar.draw(window);
	window.draw(m_texts[PLAYER]);
	window.draw(m_texts[COMPUTER]);
}

ToolBar_Buttons Board::press(const sf::Vector2f& position)
{
	m_availableColors.clear();

	for (int i = 0; i < COLORS.size(); i++)
	{
		if (m_toolBar.getClickedColor(position) == COLORS[i] && COLORS[i] != m_computerColor && COLORS[i] != m_playerColor)
		{
			m_playerColor = COLORS[i];
			setCurrentColor(m_playersHexagons, COLORS[i]);
			m_bfs.runBfs(m_grid, m_playersHexagons, HEIGHT - 1, 0, COLORS[i], 1);
			m_playerPoints = m_playersHexagons.size() / NUM_OF_HEXAGONS;
			m_texts[PLAYER].setString("PLAYER: " + std::to_string(m_playerPoints));
			fillAvailableColors();
			return ToolBar_Buttons::color;
		}
	}
	if (m_toolBar.getClickedReset(position))
	{
		return ToolBar_Buttons::reset;
	}

	return ToolBar_Buttons::blockedColor;
}

void Board::moveComputer(Level level)
{
	int colorNum;
	if (level == Level::easy)
	{
		colorNum = rand() % 4;
		m_computerColor = m_availableColors[colorNum];

	}
	else if (level == Level::medium)
	{
		m_computerColor = m_bfs.getMediumColor(m_grid, m_computersHexagons, m_availableColors);
	}
	else if (level == Level::hard)
	{

		m_computerColor = m_bfs.getBestColor(m_grid, m_computersHexagons, m_availableColors);
	}

	setCurrentColor(m_computersHexagons, m_computerColor);
	m_bfs.runBfs(m_grid, m_computersHexagons, 0, HEIGHT - 1, m_computerColor, 0);
	m_computerPoints = m_computersHexagons.size() / NUM_OF_HEXAGONS;
	m_texts[COMPUTER].setString("COMPUTER: " + std::to_string(m_computerPoints));
	fillAvailableColors();
	m_toolBar.updateNotAvailable(m_availableColors);

}

void Board::setCurrentColor(std::vector<Hexagon>& vectorToFill, sf::Color color)
{
	int row, col;
	for (size_t i = 0; i < vectorToFill.size(); i++)
	{
		row = vectorToFill[i].getCoordinates().first;
		col = vectorToFill[i].getCoordinates().second;
		m_grid[row][col].setColor(color);
		m_grid[row][col].setVisited(false);
	}
}

bool Board::checkWonOrLost(sf::RenderWindow& window)
{
	if (m_computerPoints >= 0.5)
	{
		window.clear();
		window.display();
		return true;
	}

	else if (m_playerPoints >= 0.5)
	{
		m_playerWon = true;
		window.clear();
		window.display();
		return true;
	}
	return false;
}

bool Board::drawFinishScreen(sf::RenderWindow& window, sf::Event event)
{
	while (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (m_playerWon)
			window.draw(m_texts[WIN]);
		else
			window.draw(m_texts[LOSE]);

		window.draw(m_texts[TRY_AGAIN]);
		window.display();
	}
	return true;
}

void Board::fillAvailableColors()
{
	m_availableColors.clear();
	for (size_t i = 0; i < COLORS.size(); i++)
	{
		if (COLORS[i] != m_computerColor && COLORS[i] != m_playerColor)
			m_availableColors.push_back(COLORS[i]);
	}
}