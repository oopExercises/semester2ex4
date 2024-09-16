#include "Bfs.h"
#include <queue>

void Bfs::runBfs(std::vector<std::vector<Hexagon>>& grid, std::vector<Hexagon>& hexagonsVector, int row, int col, sf::Color targetColor, bool player)
{
	hexagonsVector.clear();

	if (player)
		hexagonsVector.push_back(grid[HEIGHT - 1][0]);
	else
		hexagonsVector.push_back(grid[0][HEIGHT - 1]);

	int numRows = grid.size();
	int numCols = grid[0].size();
	std::queue<std::pair<int, int>>q;

	q.push(std::pair(row, col));

	while (!q.empty())
	{
		int r = q.front().first;
		int c = q.front().second;
		grid[r][c].setVisited(true);
		q.pop();

		int* diffCol = (r % 2 == 0) ? diffColOdd : diffColEven;

		for (int i = 0; i < 6; i++)
		{
			int nr = r + diffRow[i];
			int nc = c + diffCol[i];

			if (nr >= 0 && nr < numRows && nc >= 0 && nc < numCols && grid[nr][nc].getColor() == targetColor && !grid[nr][nc].getVisited())
			{
				grid[nr][nc].setVisited(true);

				if (player)
					grid[nr][nc].setOutlineColor(sf::Color::White);
				else
					grid[nr][nc].setOutlineColor(sf::Color(210, 85, 150));

				q.push(std::pair(nr, nc));
				hexagonsVector.push_back(grid[nr][nc]);
			}
		}

	}
}

sf::Color Bfs::getBestColor(const std::vector<std::vector<Hexagon>> grid, const std::vector<Hexagon> computerHexagons, const std::vector<sf::Color> availableColors)
{

	int counter = 0;
	int maxCounter = 0;
	sf::Color bestColor;

	int numRows = grid.size();
	int numCols = grid[0].size();
	std::queue<std::pair<int, int>>q;

	for (auto color : availableColors)
	{
		std::vector<std::vector<Hexagon>> tempGrid = grid;
		std::vector<Hexagon> tempComputerHexagons = computerHexagons;
		q.push(std::pair(0, HEIGHT - 1));
		counter = 0;
		setTempCompColor(tempComputerHexagons, tempGrid, color);

		while (!q.empty())
		{
			int r = q.front().first;
			int c = q.front().second;
			tempGrid[r][c].setVisited(true);
			q.pop();

			int* diffCol = (r % 2 == 0) ? diffColOdd : diffColEven;

			for (int i = 0; i < 6; i++)
			{
				int nr = r + diffRow[i];
				int nc = c + diffCol[i];

				if (nr >= 0 && nr < numRows && nc >= 0 && nc < numCols && tempGrid[nr][nc].getColor() == color && !tempGrid[nr][nc].getVisited())
				{
					counter++;
					tempGrid[nr][nc].setVisited(true);
					q.push(std::pair(nr, nc));
					tempComputerHexagons.push_back(tempGrid[nr][nc]);
				}

			}

		}
		if (counter > maxCounter)
		{
			maxCounter = counter;
			bestColor = color;
		}
	}
	return bestColor;
}

void Bfs::setTempCompColor(std::vector<Hexagon>& tempComputerHexagons, std::vector<std::vector<Hexagon>>& tempGrid, sf::Color color)
{
	int row, col;
	for (size_t i = 0; i < tempComputerHexagons.size(); i++)
	{
		row = tempComputerHexagons[i].getCoordinates().first;
		col = tempComputerHexagons[i].getCoordinates().second;
		tempGrid[row][col].setColor(color);
		tempGrid[row][col].setVisited(false);
	}
}

sf::Color Bfs::getMediumColor(const std::vector<std::vector<Hexagon>> grid, const std::vector<Hexagon> computerHexagons, const std::vector<sf::Color> availableColors)
{
	int colorsCounter[4] = { 0 };
	int maxCounter = 0;
	sf::Color bestColor;
	sf::Color color;
	int numRows = grid.size();
	int numCols = grid[0].size();
	std::queue<std::pair<int, int>>q;
	int index = 0;

	std::vector<std::vector<Hexagon>> tempGrid = grid;
	std::vector<Hexagon> tempComputerHexagons = computerHexagons;


	for (auto hexagon : computerHexagons)
	{
		q.push(hexagon.getCoordinates());
		int r = q.front().first;
		int c = q.front().second;
		tempGrid[r][c].setVisited(true);
		q.pop();

		int* diffCol = (r % 2 == 0) ? diffColOdd : diffColEven;

		for (int i = 0; i < 6; i++)
		{
			int nr = r + diffRow[i];
			int nc = c + diffCol[i];

			if (nr >= 0 && nr < numRows && nc >= 0 && nc < numCols && !tempGrid[nr][nc].getVisited())
			{
				if (tempGrid[nr][nc].getColor() == availableColors[0])
					colorsCounter[0]++;
				else if (tempGrid[nr][nc].getColor() == availableColors[1])
					colorsCounter[1]++;
				else if (tempGrid[nr][nc].getColor() == availableColors[2])
					colorsCounter[2]++;
				else if (tempGrid[nr][nc].getColor() == availableColors[3])
					colorsCounter[3]++;

				tempGrid[nr][nc].setVisited(true);

			}
		}
	}


	for (int i = 0; i < 4; i++)
	{

		if (colorsCounter[i] > maxCounter)
		{
			maxCounter = colorsCounter[i];
			index = i;
		}
	}
	return availableColors[index];
}
