#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <Windows.h>
#include "ClassButton.h"
#define auxiliary_functions_h
#undef min
#undef max
#define auxilary_functions_H
#define coloration_h

std::string shorteningTheString(const std::string& path);

void setNewPath(std::string nameOfPath, std::string namePath);
std::string checkingForPresenceOfPath(std::string nameOfPath);
sf::Color SetColor(std::string col);
std::string get—urrentPath();

void shell(std::string & pathUser);

void settingWindow(std::string headerText, std::string , std::string text) {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	auto icon = sf::Image();
	if (!icon.loadFromFile(get—urrentPath() + "\\textures\\application\\settings.png"));

	sf::RenderWindow settingsWindow(sf::VideoMode(600, 250), headerText, sf::Style::None, settings);
	settingsWindow.setActive(true);
	settingsWindow.setIcon(icon.getSize().x,icon.getSize().y,icon.getPixelsPtr());
	
	SFMLButton pathButton1(500, 50, 20, 25, 50, SetColor("pathColor"));
	SFMLButton pathButton2(500, 50, 20, 25, 90, SetColor("pathColor"));
	SFMLButton doneButton(100, 50, 20, 225, 10, SetColor("pathColor"));
	SFMLButton exitButton(100, 50, 20, 25, 10, SetColor("pathColor"));
	
	
	

	sf::Font speedFont;
	if (!speedFont.loadFromFile("fonts\\Roboto.ttf")) {
		std::cerr << "Speed font not load";
	}


	sf::Text pathToCrafts("Select the path where the crafts will be stored.", speedFont, 15);
	sf::Text pathToIcons("Select the path where the icons will be stored.", speedFont, 15);
	sf::Text doneText("done", speedFont, 20);
	doneText.setFillColor(SetColor("text_settings"));
	doneText.setPosition(doneButton.getPosForText(doneText));
	doneText.move(0, -3);
	sf::Text exitText("exit", speedFont, 20);
	exitText.setFillColor(SetColor("text_settings"));
	exitText.setPosition(exitButton.getPosForText(exitText));
	exitText.move(0, -3);


	
	
	
	

	HWND hwnd = settingsWindow.getSystemHandle();
	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	while (settingsWindow.isOpen()) {

		if (checkingForPresenceOfPath("path_to_crafts") != "") {
			pathToCrafts.setString(shorteningTheString(checkingForPresenceOfPath("path_to_crafts")));
			pathToCrafts.setFillColor(SetColor("text_settings"));
		}
		else {
			pathToCrafts.setFillColor(SetColor("text_settings_disable"));
		}
		pathToCrafts.setPosition(pathButton1.getPosForText(pathToCrafts));

		if (checkingForPresenceOfPath("path_to_src_icons_from_mod") != "") {
			pathToIcons.setString(shorteningTheString(checkingForPresenceOfPath("path_to_src_icons_from_mod")));
			pathToIcons.setFillColor(SetColor("text_settings"));
		}
		else {
			pathToIcons.setFillColor(SetColor("text_settings_disable"));
		}
		pathToIcons.setPosition(pathButton2.getPosForText(pathToIcons));

		sf::Event event;
		while (settingsWindow.pollEvent(event)) {
		

			if (event.type == sf::Event::Closed) {
				settingsWindow.close();
			}
			
			if (pathButton1.IsMouseOnButton(sf::Mouse::getPosition(settingsWindow))) {
				pathButton1.setOutline(SetColor("outline_main"), 5);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
					std::string namePath = "";
					shell(namePath);
					if (namePath != "") {
						setNewPath("path_to_crafts", namePath);
					}
					SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				}
			}
			else {
				pathButton1.setOutline(SetColor("outline_path_color"), 5);
			}

			if (pathButton2.IsMouseOnButton(sf::Mouse::getPosition(settingsWindow))) {
				pathButton2.setOutline(SetColor("outline_main"), 5);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
					std::string namePath = "";
					shell(namePath);
					if (namePath != "") {
						setNewPath("path_to_src_icons_from_mod", namePath);
					}
					
					SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				}
			}
			else {
				pathButton2.setOutline(SetColor("outline_path_color"), 5);
			}

			if (doneButton.IsMouseOnButton(sf::Mouse::getPosition(settingsWindow))) {
				doneButton.setOutline(SetColor("outline_main"), 5);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					if (checkingForPresenceOfPath("path_to_crafts") == "") {
						setNewPath("path_to_crafts", get—urrentPath()+"\\crafts");
					}
					if (checkingForPresenceOfPath("path_to_src_icons_from_mod") == "") {
						setNewPath("path_to_src_icons_from_mod", get—urrentPath() + "\\textures\\creator\\icons\\minecraft");
					}
					return;
				}
			}
			else {
				doneButton.setOutline(SetColor("outline_path_color"), 5);
			}

			if (exitButton.IsMouseOnButton(sf::Mouse::getPosition(settingsWindow))) {
				exitButton.setOutline(SetColor("outline_main"), 5);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					exit(0);
				}
			}
			else {
				exitButton.setOutline(SetColor("outline_path_color"), 5);
			}

		}

		if (sf::Mouse::getPosition().x < settingsWindow.getPosition().x || sf::Mouse::getPosition().x > settingsWindow.getPosition().x + settingsWindow.getSize().x) {
			sf::Mouse::setPosition(sf::Vector2i(settingsWindow.getPosition().x + settingsWindow.getSize().x / 2, sf::Mouse::getPosition().x));
		}
		
		if (sf::Mouse::getPosition().y < settingsWindow.getPosition().y || sf::Mouse::getPosition().y > settingsWindow.getPosition().y + settingsWindow.getSize().y) {
			sf::Mouse::setPosition(sf::Vector2i(sf::Mouse::getPosition().x, settingsWindow.getPosition().y + settingsWindow.getSize().y / 2));
		}

		

		
		settingsWindow.clear(SetColor("background"));
		settingsWindow.draw(pathButton1);
		settingsWindow.draw(pathButton2);
		
		
		settingsWindow.draw(doneButton);
		settingsWindow.draw(doneText);
		settingsWindow.draw(exitButton);
		settingsWindow.draw(exitText);

		
		settingsWindow.draw(pathToIcons);
		settingsWindow.draw(pathToCrafts);

		settingsWindow.display();
	}
}



void startWindow() {
	settingWindow("Start settings", "", "");

	
}

void startSettingsWindow() {
	settingWindow("settings", "", "");
}


