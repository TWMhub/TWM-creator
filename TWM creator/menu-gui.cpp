#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <Windows.h>
#undef min
#undef max
#include "SFML/Graphics.hpp"
#include "rapidjson/document.h"
//#include "ClassButtonSFML.h"
#include "ClassButton.h"
#include "coloration.h"
#include "auxiliary functions.h"
#include "modsMenuClass.h"


using std::filesystem::current_path;

void setTextShadow(sf::Text& text, sf::Color shadowColor);
void removeTextShadow(sf::Text& text, sf::Color textColor);

void startWindow();
void startSettingsWindow();
bool isPathsEmpty();
void craftCreatorWindow(sf::RenderWindow & menu);



std::string chekVersion();

int menu() {

	bool isSettingsActive = false;
	

	if (isPathsEmpty()) {
		isSettingsActive = true;
	}

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow menu(sf::VideoMode::getDesktopMode(), "TWM creator by depozit", sf::Style::None , settings);
	menu.setFramerateLimit(60);
	menu.setVerticalSyncEnabled(true);
	

	MenuMain MainMenu;
	MenuSettings SettingsMenu;

	MainMenu.initialization(menu);
	SettingsMenu.initialization(menu);


	sf::Texture backgroundTexture;
	sf::Sprite backgroundTextureRect;
	if (!backgroundTexture.loadFromFile("textures\\application\\!back.png")) {
		std::cerr << "Background texture not load";
	}
	
	backgroundTextureRect.setTexture(backgroundTexture);

	sf::Image iconForMenu;
	if (!iconForMenu.loadFromFile("textures\\application\\icon.png")) {
		std::cerr << "icon not load" << std::endl;
	}
	menu.setIcon(iconForMenu.getSize().x, iconForMenu.getSize().y, iconForMenu.getPixelsPtr());

	while (menu.isOpen()) {

		sf::Event event;
		while (menu.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				menu.close();
			}

			if (!isSettingsActive) {
				MainMenu.EventHandler(event, menu, isSettingsActive);
			}
			else {
				SettingsMenu.EventHandler(event, menu, isSettingsActive);
			}
		}
		
		menu.clear(SetColor("background"));
		menu.draw(backgroundTextureRect);
		
		if (!isSettingsActive) {
			MainMenu.draw(menu);
		}
		else {
			SettingsMenu.draw(menu);
		}
		menu.display();
	}

	return 0;
}
