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
void craftCreatorWindow();
std::string chekVersion();

int main() {

	if (isPathsEmpty()) {
		startWindow();
	}

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow menu(sf::VideoMode::getDesktopMode(),"TWM creator by depozit",sf::Style::Fullscreen,settings);

	menu.setFramerateLimit(60);
	menu.setVerticalSyncEnabled(true);
	
	sf::Font speedFont,lazerFont;
	if (!speedFont.loadFromFile("fonts\\speed-speed-700.ttf")) {
		std::cerr << "Speed font not load";
	}
	if (!lazerFont.loadFromFile("fonts\\Roboto.ttf")) {
		std::cerr << "Lazer font not load";
	}

	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("textures\\application\\back.png")) {
		std::cerr << "Background texture not load";
	}


	sf::Sprite backgroundTextureRect;
	backgroundTextureRect.setTexture(backgroundTexture);

	

	sf::Text name1,name2,versionText;
	name1.setFont(speedFont);
	name1.setString("TWM");
	name1.setCharacterSize(80);
	name1.setFillColor(SetColor("text_main"));
	name1.setPosition(sf::Vector2f(120, 100));
	name1.setOutlineColor(SetColor("outline_main"));
	name1.setOutlineThickness(2.5);

	name2.setFont(speedFont);
	name2.setString("creator");
	name2.setCharacterSize(45);
	name2.setFillColor(SetColor("text_main"));
	name2.setPosition(sf::Vector2f(520 - name2.getGlobalBounds().width, 5 + name1.getGlobalBounds().top + name1.getGlobalBounds().height));
	name2.setOutlineColor(SetColor("outline_main"));
	name2.setOutlineThickness(1.5);

	versionText.setFont(speedFont);
	versionText.setString(chekVersion());
	versionText.setCharacterSize(15);
	versionText.setFillColor(SetColor("text_main"));
	versionText.setPosition(name2.getGlobalBounds().left+name2.getGlobalBounds().width-versionText.getGlobalBounds().width, name2.getGlobalBounds().top + name2.getGlobalBounds().height + 10);


	SFMLButton creatorButton(400,140,60,SetColor("button"));
	creatorButton.setPos(120, 330);
	
	SFMLButton drawerButton(400, 140, 60, SetColor("disabled_button"));
	drawerButton.setPos(creatorButton.getPos().x, creatorButton.getPos().y + 40 + creatorButton.getSize().y);

	SFMLButton settingsButton(300, 105, 45, SetColor("button"));
	settingsButton.setPos(creatorButton.getPos().x+creatorButton.getSize().x/2-settingsButton.getSize().x/2, creatorButton.getPos().y + 40 * 2 + drawerButton.getSize().y * 2);

	SFMLButton exitButton(200, 95, 45, SetColor("button"));
	exitButton.setPos(creatorButton.getPos().x + creatorButton.getSize().x / 2 - exitButton.getSize().x / 2, settingsButton.getPos().y + settingsButton.getSize().y + 40);

	float shadowX = 7, shadowY = shadowX;
	SFMLButton ShadowButton1(400, 140, 60, SetColor("outline", 200));
	SFMLButton ShadowButton2(300, 105, 45, SetColor("outline", 200));
	SFMLButton ShadowButton3(200, 95, 45, SetColor("outline", 200));
	

	sf::Text nameButtonCraftCreator, nameButtonTexturePainter, nameButtonSettings, nameButtonExit;

	nameButtonCraftCreator.setFont(lazerFont);
	nameButtonCraftCreator.setString("Craft Creator");
	nameButtonCraftCreator.setCharacterSize(35);
	nameButtonCraftCreator.setFillColor(SetColor("text"));
	nameButtonCraftCreator.setPosition(creatorButton.getPosForText(nameButtonCraftCreator));
	nameButtonCraftCreator.setOutlineThickness(1);
	nameButtonCraftCreator.setOutlineColor(SetColor("outline"));
	nameButtonCraftCreator.setLetterSpacing(1.5f);

	nameButtonTexturePainter.setFont(lazerFont);
	nameButtonTexturePainter.setString("Texture  Painter");
	nameButtonTexturePainter.setCharacterSize(35);
	nameButtonTexturePainter.setFillColor(SetColor("text"));
	nameButtonTexturePainter.setPosition(drawerButton.getPosForText(nameButtonTexturePainter));
	nameButtonTexturePainter.setOutlineThickness(1);
	nameButtonTexturePainter.setOutlineColor(SetColor("outline"));
	nameButtonTexturePainter.setLetterSpacing(1.5f);
	
	nameButtonSettings.setFont(lazerFont);
	nameButtonSettings.setString("settings");
	nameButtonSettings.setCharacterSize(25);
	nameButtonSettings.setFillColor(SetColor("text"));
	nameButtonSettings.setPosition(settingsButton.getPosForText(nameButtonSettings));
	nameButtonSettings.setOutlineThickness(1);
	nameButtonSettings.setOutlineColor(SetColor("outline"));
	nameButtonSettings.setLetterSpacing(1.5f);
	
	nameButtonExit.setFont(lazerFont);
	nameButtonExit.setString("exit");
	nameButtonExit.setCharacterSize(25);
	nameButtonExit.setFillColor(SetColor("text"));
	nameButtonExit.setPosition(exitButton.getPosForText(nameButtonExit));
	nameButtonExit.setOutlineThickness(1);
	nameButtonExit.setOutlineColor(SetColor("outline"));
	nameButtonExit.setLetterSpacing(1.5f);

	
	while (menu.isOpen()) {

		sf::Event event;
		while (menu.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				menu.close();
			}

			if (creatorButton.IsMouseOnButton(sf::Mouse::getPosition())) {
				creatorButton.setColor(SetColor("button_shade"));
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					menu.close();
					craftCreatorWindow();
				}
			}
			else {
				creatorButton.setColor(SetColor("button"));
			}

			if (settingsButton.IsMouseOnButton(sf::Mouse::getPosition())) {
				settingsButton.setColor(SetColor("button_shade"));
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					menu.setVisible(false);
					startSettingsWindow();
					menu.setVisible(true);
				
				}
			}
			else {
				settingsButton.setColor(SetColor("button"));
			}

			if (exitButton.IsMouseOnButton(sf::Mouse::getPosition())) {
				exitButton.setColor(SetColor("button_shade"));
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					menu.close();
					return 1;
				}
			}
			else {
				exitButton.setColor(SetColor("button"));
			}


		}
		
		
		
		menu.clear(SetColor("background"));
		menu.draw(backgroundTextureRect);

		menu.draw(name1);
		menu.draw(name2);
		menu.draw(versionText);

		ShadowButton1.setPos(creatorButton.getPos().x + shadowX, creatorButton.getPos().y + shadowY);
		menu.draw(ShadowButton1);
		menu.draw(creatorButton);

		setTextShadow(nameButtonCraftCreator, SetColor("outline"));
		menu.draw(nameButtonCraftCreator);
		removeTextShadow(nameButtonCraftCreator, SetColor("text"));
		menu.draw(nameButtonCraftCreator);


		ShadowButton1.setPos(drawerButton.getPos().x + shadowX, drawerButton.getPos().y + shadowY);
		menu.draw(ShadowButton1);
		menu.draw(drawerButton);

		setTextShadow(nameButtonTexturePainter, SetColor("outline"));
		menu.draw(nameButtonTexturePainter);
		removeTextShadow(nameButtonTexturePainter, SetColor("text"));
		menu.draw(nameButtonTexturePainter);


		ShadowButton2.setPos(settingsButton.getPos().x + shadowX, settingsButton.getPos().y + shadowY);
		menu.draw(ShadowButton2);
		menu.draw(settingsButton);

		setTextShadow(nameButtonSettings, SetColor("outline"));
		menu.draw(nameButtonSettings);
		removeTextShadow(nameButtonSettings, SetColor("text"));
		menu.draw(nameButtonSettings);


		ShadowButton3.setPos(exitButton.getPos().x + shadowX, exitButton.getPos().y + shadowY);
		menu.draw(ShadowButton3);
		menu.draw(exitButton);

		setTextShadow(nameButtonExit, SetColor("outline"));
		menu.draw(nameButtonExit);
		removeTextShadow(nameButtonExit, SetColor("text"));
		menu.draw(nameButtonExit);


		menu.display();
	}

	
	return 0;
}
