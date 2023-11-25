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

int main() {

	if (isPathsEmpty()) {
		startWindow();
	}

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow menu(sf::VideoMode::getDesktopMode(), "TWM creator by depozit", sf::Style::Fullscreen, settings);
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

	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("textures\\application\\!back.png")) {
		std::cerr << "Background texture not load";
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


	SFMLButton creatorButton(400,90,5,SetColor("menu_button_active"));
	creatorButton.setCenterByWindowByX(menu,350);
	
	SFMLButton drawerButton(400, 90, 5, SetColor("menu_button_inactive"));
	drawerButton.setPos(creatorButton.getPos().x, creatorButton.getPos().y + 40 + creatorButton.getSize().y);

	SFMLButton settingsButton(400, 90, 2.5, SetColor("menu_button_active"));
	settingsButton.setPos(creatorButton.getPos().x + creatorButton.getSize().x / 2 - settingsButton.getSize().x / 2, creatorButton.getPos().y + 40 * 2 + drawerButton.getSize().y * 2);

	SFMLButton exitButton(200, 75, 2.5, SetColor("menu_button_active"));
	exitButton.setPos(creatorButton.getPos().x + creatorButton.getSize().x / 2 - exitButton.getSize().x / 2, settingsButton.getPos().y + settingsButton.getSize().y + 40);
	

	sf::Text nameButtonCraftCreator, nameButtonTexturePainter, nameButtonSettings, nameButtonExit;

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
				creatorButton.setColor(SetColor("menu_button_active"));
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
				settingsButton.setColor(SetColor("menu_button_active"));
			}

			if (exitButton.IsMouseOnButton(sf::Mouse::getPosition())) {
				exitButton.setColor(SetColor("button_shade"));
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					menu.close();
					return 1;
				}
			}
			else {
				exitButton.setColor(SetColor("menu_button_active"));
			}


		}
		
		
		
		menu.clear(SetColor("background"));
		menu.draw(backgroundTextureRect);

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
	


		menu.display();
	}

	
	return 0;
}
