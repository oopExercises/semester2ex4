#pragma once
#include "Hexagon.h"

class Bfs
{
private:
	int diffRow[6] = {-1, -1, 0, 0, 1, 1};
	int diffColOdd[6] = { -1, 0, -1, 1, -1, 0 };
	int diffColEven[6] = { 0, 1, -1, 1, 0, 1 };
public:
	void runBfs(std::vector<std::vector<Hexagon>>& grid, std::vector<Hexagon>&, int row, int col, sf::Color targetColor, bool);//to color the hexagons according to the chosen color
	sf::Color getBestColor(const std::vector<std::vector<Hexagon>> grid , const std::vector<Hexagon> computerHexagons , const std::vector<sf::Color> availableColors) ;
	void setTempCompColor(std::vector<Hexagon>&, std::vector<std::vector<Hexagon>>&, sf::Color);
	sf::Color getMediumColor(const std::vector<std::vector<Hexagon>> grid, const std::vector<Hexagon> computerHexagons, const std::vector<sf::Color> availableColors);
};