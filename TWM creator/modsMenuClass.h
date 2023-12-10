#pragma once
#include "SFML/Graphics.hpp"
#include "ClassButton.h"
#include <iostream>
#include <vector>
#define coloration_h
#define auxiliary_functions_h

std::string chekVersion();
sf::Color SetColor(std::string col);
sf::Color SetColor(std::string col, float alphaColor);
void craftCreatorWindow(sf::RenderWindow& menu);


class MenuMain {
public:

	void initialization(const sf::RenderWindow& menu) {

		if (!speedFont.loadFromFile("fonts\\speed-speed-700.ttf")) {
			std::cerr << "Speed font not load";
		}
		if (!lazerFont.loadFromFile("fonts\\Roboto.ttf")) {
			std::cerr << "Lazer font not load";
		}
		if (!concielFont.loadFromFile("fonts\\concielianalpha.ttf")) {
			std::cerr << "conciel font not load";
		}
		if (!brunoFont.loadFromFile("fonts\\BrunoAceSC-Regular.ttf")) {
			std::cerr << "bruno font not load";
		}

		if (!folderTexture.loadFromFile("textures\\application\\folder.png")) {
			std::cerr << "foldaer texture not load";
		}
		name1.setFont(concielFont);
		name1.setString("TWM");
		name1.setCharacterSize(160);
		name1.setFillColor(SetColor("text_name_main"));
		name1.setPosition(sf::Vector2f(1920 / 2 - name1.getGlobalBounds().width / 2 - 80, 15));

		name2.setFont(concielFont);
		name2.setString("creator");
		name2.setCharacterSize(95);
		name2.setFillColor(SetColor("text_name_second"));
		name2.setPosition(sf::Vector2f(1920 / 2 - name2.getGlobalBounds().width / 2 + 50, name1.getGlobalBounds().top + name1.getGlobalBounds().height - 30));


		versionText.setFont(concielFont);
		versionText.setString(chekVersion());
		versionText.setCharacterSize(15);
		versionText.setFillColor(SetColor("text_name_second"));
		versionText.setPosition(name2.getGlobalBounds().left + name2.getGlobalBounds().width - versionText.getGlobalBounds().width, name2.getGlobalBounds().top + name2.getGlobalBounds().height + 10);

		SFMLButton creatorButton1(500, 90, 5, SetColor("menu_button_active", 230));
		creatorButton1.setCenterByWindowByX(menu, 350);

		SFMLButton drawerButton1(500, 90, 5, SetColor("menu_button_inactive", 230));
		drawerButton1.setPos(creatorButton1.getPos().x, creatorButton1.getPos().y + 40 + creatorButton1.getSize().y);

		SFMLButton settingsButton1(500, 90, 2.5, SetColor("menu_button_active", 230));
		settingsButton1.setPos(creatorButton1.getPos().x + creatorButton1.getSize().x / 2 - settingsButton1.getSize().x / 2, creatorButton1.getPos().y + 40 * 2 + drawerButton1.getSize().y * 2);

		SFMLButton exitButton1(250, 75, 2.5, SetColor("menu_button_active", 230));
		exitButton1.setPos(creatorButton1.getPos().x + creatorButton1.getSize().x / 2 - exitButton1.getSize().x / 2, settingsButton1.getPos().y + settingsButton1.getSize().y + 40);

		creatorButton = creatorButton1;
		drawerButton = drawerButton1;
		settingsButton = settingsButton1;
		exitButton= exitButton1;

		nameButtonCraftCreator.setFont(brunoFont);
		nameButtonCraftCreator.setString("Craft Creator");
		nameButtonCraftCreator.setCharacterSize(30);
		nameButtonCraftCreator.setFillColor(SetColor("menu_text"));
		nameButtonCraftCreator.setPosition(creatorButton.getPosForText(nameButtonCraftCreator));
		nameButtonCraftCreator.move(0, -5);

		nameButtonTexturePainter.setFont(brunoFont);
		nameButtonTexturePainter.setString("Texture  Painter");
		nameButtonTexturePainter.setCharacterSize(30);
		nameButtonTexturePainter.setFillColor(SetColor("menu_text"));
		nameButtonTexturePainter.setPosition(drawerButton.getPosForText(nameButtonTexturePainter));
		nameButtonTexturePainter.move(0, -5);

		nameButtonSettings.setFont(brunoFont);
		nameButtonSettings.setString("settings");
		nameButtonSettings.setCharacterSize(30);
		nameButtonSettings.setFillColor(SetColor("menu_text"));
		nameButtonSettings.setPosition(settingsButton.getPosForText(nameButtonSettings));
		nameButtonSettings.move(0, -5);

		nameButtonExit.setFont(brunoFont);
		nameButtonExit.setString("exit");
		nameButtonExit.setCharacterSize(25);
		nameButtonExit.setFillColor(SetColor("menu_text"));
		nameButtonExit.setPosition(exitButton.getPosForText(nameButtonExit));
		nameButtonExit.move(0, -5);
	}

	void EventHandler(sf::Event& event, sf::RenderWindow& menu, bool& isSettingsActive) {
		if (creatorButton.IsMouseOnButton(sf::Mouse::getPosition())) {
				creatorButton.setColor(SetColor("button_shade"));
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					//menu.close();
					craftCreatorWindow(menu);
				}
			}
			else {
				creatorButton.setColor(SetColor("menu_button_active", 230));
			}

			if (settingsButton.IsMouseOnButton(sf::Mouse::getPosition())) {
				settingsButton.setColor(SetColor("button_shade"));
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					isSettingsActive = !isSettingsActive;
				}
			}
			else {
				settingsButton.setColor(SetColor("menu_button_active", 230));
			}

			if (exitButton.IsMouseOnButton(sf::Mouse::getPosition())) {
				exitButton.setColor(SetColor("button_shade"));
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					menu.close();
					return;
				}
			}
			else {
				exitButton.setColor(SetColor("menu_button_active", 230));
			}
	}

	void draw(sf::RenderWindow& menu) {
		menu.draw(name1);
		menu.draw(name2);
		menu.draw(versionText);
		menu.draw(creatorButton);
		menu.draw(nameButtonCraftCreator);
		menu.draw(drawerButton);
		menu.draw(nameButtonTexturePainter);
		menu.draw(settingsButton);
		menu.draw(nameButtonSettings);
		menu.draw(exitButton);
		menu.draw(nameButtonExit);
		
	}

	void move(sf::Vector2f pos) {
		name1.move(pos);
		name2.move(pos);
		versionText.move(pos);
		nameButtonCraftCreator.move(pos);
		nameButtonTexturePainter.move(pos);
		nameButtonSettings.move(pos);
		nameButtonExit.move(pos);
		creatorButton.move(pos);
		drawerButton.move(pos);
		settingsButton.move(pos);
		exitButton.move(pos);
	}

private:
	void setBasePos() {
		objectPos.push_back(name1.getPosition());
		objectPos.push_back(name2.getPosition());
		objectPos.push_back(versionText.getPosition());
		objectPos.push_back(nameButtonCraftCreator.getPosition());
		objectPos.push_back(nameButtonTexturePainter.getPosition());
		objectPos.push_back(nameButtonSettings.getPosition());
		objectPos.push_back(nameButtonExit.getPosition());
		objectPos.push_back(creatorButton.getPos());
		objectPos.push_back(drawerButton.getPos());
		objectPos.push_back(settingsButton.getPos());
		objectPos.push_back(exitButton.getPos());
	}
	sf::Texture folderTexture;
	sf::Text name1, name2, versionText;
	sf::Font speedFont, lazerFont, concielFont, brunoFont;
	SFMLButton creatorButton, drawerButton, settingsButton, exitButton;
	sf::Text nameButtonCraftCreator, nameButtonTexturePainter, nameButtonSettings, nameButtonExit;
	std::vector<sf::Vector2f> objectPos;
};



class MenuSettings {
public:
	void initialization(const sf::RenderWindow& menu) {

		if (!folderTexture.loadFromFile("textures\\application\\folder.png")) {
			std::cerr << "foldaer texture not load";
		}

		if (!brunoFont.loadFromFile("fonts\\BrunoAceSC-Regular.ttf")) {
			std::cerr << "bruno font not load";
		}

		SFMLButton backSettingsI(600, 400, 5, SetColor("settings_back", 245));
		backSettingsI.setCenterByWindow(menu);

		SFMLButton folderPath1I(50, 50, 5, SetColor("setings_folder_background"));
		folderPath1I.setPos(backSettingsI.getGlobalBounds().left + 50, backSettingsI.getGlobalBounds().top + 200);

		SFMLButton folderPath2I(50, 50, 5, SetColor("setings_folder_background"));
		folderPath2I.setPos(backSettingsI.getGlobalBounds().left + 50, backSettingsI.getGlobalBounds().top + 200 + 10 + folderPath1I.getGlobalBounds().height);

		SFMLButton pathRect1I(420, 50, 5, SetColor("settings_path_rect", 200));
		pathRect1I.setPos(folderPath1I.getGlobalBounds().left + folderPath1I.getGlobalBounds().width + 10, folderPath1I.getGlobalBounds().top);

		SFMLButton pathRect2I(420, 50, 5, SetColor("settings_path_rect", 200));
		pathRect2I.setPos(folderPath2I.getGlobalBounds().left + folderPath2I.getGlobalBounds().width + 10, folderPath2I.getGlobalBounds().top);

		SFMLButton returnButtonI(100, 50, 5, SetColor("setings_folder_background"));
		returnButtonI.setPos(backSettingsI.getGlobalBounds().left + backSettingsI.getGlobalBounds().width - returnButtonI.getGlobalBounds().width - 5,
			backSettingsI.getGlobalBounds().top + backSettingsI.getGlobalBounds().height - returnButtonI.getGlobalBounds().height - 5);

		returnButtonText.setFont(brunoFont);
		returnButtonText.setString("return");
		returnButtonText.setCharacterSize(20);
		returnButtonText.setFillColor(SetColor("menu_text"));
		returnButtonText.setPosition(returnButtonI.getPosForText(returnButtonText));
		returnButtonText.move(sf::Vector2f(0, -5));

		backSettings = backSettingsI;
		folderPath1 = folderPath1I;
		folderPath2 = folderPath2I;
		pathRect1 = pathRect1I;
		pathRect2 = pathRect2I;
		returnButton = returnButtonI;

		setBasePos();
	}

	void draw(sf::RenderWindow& menu) {
		menu.draw(backSettings);
		folderPath1.drawSprite(folderTexture, sf::Vector2f(0, 0), sf::Vector2f(0.05, 0.05), menu);
		folderPath2.drawSprite(folderTexture, sf::Vector2f(0, 0), sf::Vector2f(0.05, 0.05), menu);
		menu.draw(pathRect1);
		menu.draw(pathRect2);
		menu.draw(returnButton);
		menu.draw(returnButtonText);
	}

	void move(sf::Vector2f pos) {
		returnButtonText.move(pos);
		backSettings.move(pos);
		folderPath1.move(pos);
		folderPath2.move(pos);
		pathRect1.move(pos);
		pathRect2.move(pos);
		returnButton.move(pos);
	}

private:

	void setBasePos() {
		objectsPos.push_back(returnButtonText.getPosition());
		objectsPos.push_back(backSettings.getPos());
		objectsPos.push_back(folderPath1.getPos());
		objectsPos.push_back(folderPath2.getPos());
		objectsPos.push_back(pathRect1.getPos());
		objectsPos.push_back(pathRect2.getPos());
		objectsPos.push_back(returnButton.getPos());
	}

	sf::Texture folderTexture;
	sf::Font brunoFont;
	sf::Text returnButtonText;
	SFMLButton backSettings, folderPath1, folderPath2, pathRect1, pathRect2, returnButton;
	std::vector<sf::Vector2f> objectsPos;
};