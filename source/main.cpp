#include "TextButton.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Layout.h"
#include <iostream>

const int mainWidth = 800;
const int mainHeight = 640;
std::string windowTitle = "Maple Asssist";

int main() {

	windowTitle = "August 14th";
	sf::RenderWindow mainWindow(sf::VideoMode(mainWidth, mainHeight), windowTitle, sf::Style::Titlebar | sf::Style::Close);

	sf::Image icon;

	icon.loadFromFile("resources\\MapleAssistant.png");
	mainWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	DPSCalc dpsCalc(mainWidth, mainHeight);


	while (mainWindow.isOpen()) {


		sf::Event event;
		while (mainWindow.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed : {
				mainWindow.close();
				break;
			}

			case sf::Event::MouseButtonPressed: {
				if (event.mouseButton.button == sf::Mouse::Left) {
					dpsCalc.isMouseOver(mainWindow);
				}

				break;
			}
			case sf::Event::TextEntered:
			{
				for (int i = 0; i < dpsCalc.tbwL.size(); i++) {
					dpsCalc.tbwL[i].textbox.typedOn(event);
				}
			}
			//case sf::Event::

			}


		}


		mainWindow.clear(sf::Color::White);

		dpsCalc.draw(mainWindow);

		mainWindow.display();

	}

	return 0;
}