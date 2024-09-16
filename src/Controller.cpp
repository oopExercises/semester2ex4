#include "Controller.h"

Controller::Controller() : m_render_window(sf::RenderWindow(sf::VideoMode(800, 800), "Six Colors Game", sf::Style::Close))
{
	m_render_window.setFramerateLimit(60);
	m_level = Level::easy;
}

void Controller::run()
{
	auto event = sf::Event();
	std::srand(std::time(nullptr));
	Board gameBoard(m_render_window);
	int chosenLevel = choseLevel(m_render_window, event);

	sf::Vector2f location;

	while (m_render_window.isOpen())
	{

		while (m_render_window.pollEvent(event) && !gameBoard.checkWonOrLost(m_render_window))
		{
			m_render_window.clear(sf::Color::White);
			gameBoard.drawScreen(m_render_window);

			m_render_window.display();
			switch (event.type)
			{
			case sf::Event::Closed:
				m_render_window.close();
				break;
			case sf::Event::MouseMoved:
				location = static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_render_window));
				break;
			case sf::Event::MouseButtonReleased:
				location = static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_render_window));
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Button::Left:
					m_clickedButton = gameBoard.press(location);
					if (m_clickedButton == ToolBar_Buttons::reset)
						run();
					else if (m_clickedButton == ToolBar_Buttons::blockedColor)
					{
						break;
					}
					else if (m_clickedButton == ToolBar_Buttons::color)
						gameBoard.moveComputer(m_level);
					break;
				}
				break;

			}
			m_render_window.clear(sf::Color::White);
			gameBoard.drawScreen(m_render_window);
			m_render_window.display();

		}
		if (gameBoard.checkWonOrLost(m_render_window))
		{
			m_render_window.clear();
			if (gameBoard.drawFinishScreen(m_render_window, event))
				run();
		}
	}
}


int Controller::choseLevel(sf::RenderWindow& window, sf::Event& event)
{
	auto& font = Manager::instance().getFont();

	sf::Text chooseLevelText("Please choose the level", font, 40);
	chooseLevelText.setPosition(200, 100);

	sf::Text easyText("Easy", font, 30);
	easyText.setPosition(350, 200);

	sf::Text mediumText("Medium", font, 30);
	mediumText.setPosition(340, 250);

	sf::Text hardText("Hard", font, 30);
	hardText.setPosition(355, 300);

	sf::Color defaultColor = sf::Color::White;
	sf::Color hoverColor = sf::Color::Yellow;

	int chosenLevel = 0;
	bool levelChosen = false;

	while (!levelChosen)
	{
		if (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
					if (easyText.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
					{
						m_level = Level::easy;
						levelChosen = true;
					}
					else if (mediumText.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
					{
						m_level = Level::medium;
						levelChosen = true;
					}
					else if (hardText.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
					{
						m_level = Level::hard;
						levelChosen = true;
					}
				}
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				easyText.setFillColor(easyText.getGlobalBounds().contains(mousePosition.x, mousePosition.y) ? hoverColor : defaultColor);
				mediumText.setFillColor(mediumText.getGlobalBounds().contains(mousePosition.x, mousePosition.y) ? hoverColor : defaultColor);
				hardText.setFillColor(hardText.getGlobalBounds().contains(mousePosition.x, mousePosition.y) ? hoverColor : defaultColor);
			}
		}

		window.clear();
		window.draw(chooseLevelText);
		window.draw(easyText);
		window.draw(mediumText);
		window.draw(hardText);
		window.display();
	}

	return chosenLevel;
}


