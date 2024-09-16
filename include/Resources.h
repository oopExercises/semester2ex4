
const std::string WIN = "win";
const std::string LOSE = "lose";
const std::string PLAYER = "PLAYER";
const std::string COMPUTER = "COMPUTER";
const std::string TRY_AGAIN = "TRY AGAIN";

const sf::Color RED = sf::Color::Red;
const sf::Color BLUE = sf::Color::Blue;
const sf::Color YELLOW = sf::Color::Yellow;
const sf::Color GREEN = sf::Color::Green;
const sf::Color CYAN = sf::Color::Cyan;
const sf::Color MAGENTA = sf::Color::Magenta;

const std::vector<sf::Color> COLORS = { RED, BLUE, YELLOW, GREEN, CYAN, MAGENTA };

const int HEXAGON_RADIUS = 13;
const int HEXAGON_SIDES_NUM = 6;
const int WIDTH = 25;
const int HEIGHT = 25;
const float NUM_OF_HEXAGONS = WIDTH * HEIGHT;
const int NUM_OF_ICONS = 7;

enum class Level
{
	easy,
	medium,
	hard
};

enum class ToolBar_Buttons
{
	reset,
	color,
	blockedColor
};


