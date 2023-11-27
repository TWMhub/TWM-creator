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

using std::filesystem::current_path;

void setTextShadow(sf::Text& text, sf::Color shadowColor);
void removeTextShadow(sf::Text& text, sf::Color textColor);

void startWindow();
void startSettingsWindow();
bool isPathsEmpty();
void craftCreatorWindow(sf::RenderWindow & menu);
std::string chekVersion();

int menu() {

	if (isPathsEmpty()) {
		startWindow();
	}

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow menu(sf::VideoMode::getDesktopMode(), "TWM creator by depozit", sf::Style::Fullscreen , settings);
	menu.setFramerateLimit(60);
	menu.setVerticalSyncEnabled(true);
	
	sf::Font speedFont, lazerFont, concielFont, brunoFont;
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


	//
	//menu
	//

	sf::Texture backgroundTexture, folderTexture;
	if (!backgroundTexture.loadFromFile("textures\\application\\!back.png")) {
		std::cerr << "Background texture not load";
	}
	if (!folderTexture.loadFromFile("textures\\application\\folder.png")) {
		std::cerr << "foldaer texture not load";
	}

	sf::Image iconForMenu;
	if (!iconForMenu.loadFromFile("textures\\application\\icon.png")) {
		std::cerr << "icon not load" << std::endl;
	}
	menu.setIcon(iconForMenu.getSize().x, iconForMenu.getSize().y, iconForMenu.getPixelsPtr());

	sf::Sprite backgroundTextureRect;
	backgroundTextureRect.setTexture(backgroundTexture);

	sf::Text name1,name2,versionText;
	name1.setFont(concielFont);
	name1.setString("TWM");
	name1.setCharacterSize(160);
	name1.setFillColor(SetColor("text_name_main"));
	name1.setPosition(sf::Vector2f(1920/2-name1.getGlobalBounds().width/2-80, 15));

	name2.setFont(concielFont);
	name2.setString("creator");
	name2.setCharacterSize(95);
	name2.setFillColor(SetColor("text_name_second"));
	name2.setPosition(sf::Vector2f(1920 / 2 - name2.getGlobalBounds().width / 2 + 50, name1.getGlobalBounds().top + name1.getGlobalBounds().height - 30));
	

	versionText.setFont(concielFont);
	versionText.setString(chekVersion());
	versionText.setCharacterSize(15);
	versionText.setFillColor(SetColor("text_name_second"));
	versionText.setPosition(name2.getGlobalBounds().left+name2.getGlobalBounds().width-versionText.getGlobalBounds().width, name2.getGlobalBounds().top + name2.getGlobalBounds().height + 10);


	SFMLButton creatorButton(500,90,5,SetColor("menu_button_active", 230));
	creatorButton.setCenterByWindowByX(menu,350);
	
	SFMLButton drawerButton(500, 90, 5, SetColor("menu_button_inactive",230));
	drawerButton.setPos(creatorButton.getPos().x, creatorButton.getPos().y + 40 + creatorButton.getSize().y);

	SFMLButton settingsButton(500, 90, 2.5, SetColor("menu_button_active", 230));
	settingsButton.setPos(creatorButton.getPos().x + creatorButton.getSize().x / 2 - settingsButton.getSize().x / 2, creatorButton.getPos().y + 40 * 2 + drawerButton.getSize().y * 2);

	SFMLButton exitButton(250, 75, 2.5, SetColor("menu_button_active", 230));
	exitButton.setPos(creatorButton.getPos().x + creatorButton.getSize().x / 2 - exitButton.getSize().x / 2, settingsButton.getPos().y + settingsButton.getSize().y + 40);
	

	sf::Text nameButtonCraftCreator, nameButtonTexturePainter, nameButtonSettings, nameButtonExit, returnButtonText;

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

	returnButtonText.setFont(brunoFont);
	returnButtonText.setString("return");
	returnButtonText.setCharacterSize(20);
	returnButtonText.setFillColor(SetColor("menu_text"));
	


	//
	//settings
	//

	SFMLButton backSettings(600, 400, 5, SetColor("background", 230));
	backSettings.setCenterByWindow(menu);

	SFMLButton folderPath1(50, 50, 5, SetColor("setings_folder_background"));	
	folderPath1.setPos(backSettings.getGlobalBounds().left + 50, backSettings.getGlobalBounds().top + 200);
	SFMLButton folderPath2(50, 50, 5, SetColor("setings_folder_background"));
	folderPath2.setPos(backSettings.getGlobalBounds().left + 50, backSettings.getGlobalBounds().top + 200 + 10 + folderPath1.getGlobalBounds().height);

	SFMLButton pathRect1(420, 50, 5, SetColor("settings_path_rect",200));
	pathRect1.setPos(folderPath1.getGlobalBounds().left + folderPath1.getGlobalBounds().width + 10, folderPath1.getGlobalBounds().top);

	SFMLButton pathRect2(420, 50, 5, SetColor("settings_path_rect", 200));
	pathRect2.setPos(folderPath2.getGlobalBounds().left + folderPath2.getGlobalBounds().width + 10, folderPath2.getGlobalBounds().top);

	SFMLButton returnButton(100, 50, 5, SetColor("setings_folder_background"));
	returnButton.setPos(backSettings.getGlobalBounds().left+ backSettings.getGlobalBounds().width - returnButton.getGlobalBounds().width - 5,
		backSettings.getGlobalBounds().top + backSettings.getGlobalBounds().height - returnButton.getGlobalBounds().height - 5);
	
	returnButtonText.setPosition(returnButton.getPosForText(returnButtonText));
	returnButtonText.move(0, -5);
	
	
	while (menu.isOpen()) {

		sf::Event event;
		while (menu.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				menu.close();
			}

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
					//sf::Thread thread(&startSettingsWindow);
					sf::Vector2u sizeWindow{ menu.getSize().x,menu.getSize().y };
					menu.setSize(sf::Vector2u(1920,1800));
					menu.setActive(false);
					startSettingsWindow();
					menu.setActive(true);
					menu.setSize(sizeWindow);
					//thread.launch();
					//thread.wait();
				
				}
			}
			else {
				settingsButton.setColor(SetColor("menu_button_active", 230));
			}

			if (exitButton.IsMouseOnButton(sf::Mouse::getPosition())) {
				exitButton.setColor(SetColor("button_shade"));
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					menu.close();
					return 1;
				}
			}
			else {
				exitButton.setColor(SetColor("menu_button_active", 230));
			}


		}
		
		
		
		menu.clear(SetColor("background"));
		menu.draw(backgroundTextureRect);

		if (false) {
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
		else {
			menu.draw(backSettings);
			folderPath1.drawSprite(folderTexture, sf::Vector2f(0, 0), sf::Vector2f(0.05, 0.05), menu);
			folderPath2.drawSprite(folderTexture, sf::Vector2f(0, 0), sf::Vector2f(0.05, 0.05), menu);
			menu.draw(pathRect1);
			menu.draw(pathRect2);
			menu.draw(returnButton);
			menu.draw(returnButtonText);
		}


		menu.display();

	
	}

	
	return 0;
}
