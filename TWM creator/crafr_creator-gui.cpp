#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include "SFML/Graphics.hpp"
#include "ClassButton.h"
#define auxiliary_functions_h
#define coloration_h

const short int COUNT_BUTTONS_ON_SCROLL_MENU = 11;
const short int DIST_BETWEEN_BUTTONS = 18;

sf::Color SetColor(std::string col);
sf::Color SetColor(std::string col, float alphaColor);

void writeAllItemsToVectors(std::vector<std::string>& itemsNames, std::vector<sf::Texture>& itemsSprites);

void writeAllItemsNames(std::vector<std::string>& allItemsNames);
void writeTextureAsThreadWithBorders(std::promise<std::vector<sf::Texture>>& promiseTextures, int topBorder, int lowBorder);

void writeTexturesToBinary(const std::vector<sf::Texture>& allTextures);
std::vector<sf::Texture> readTexturesFromBinary();

int menu();

void craftCreatorWindow(sf::RenderWindow & menuWindow) {
	
	//vector with all items 
	std::vector<std::string> allItemsNames{};
	std::vector<sf::Texture> allItemsTexture{};

	//thread
	/*try
	{

		const unsigned int avaibleCores = std::thread::hardware_concurrency();
		writeAllItemsNames(allItemsNames);
	
		std::promise<std::vector<sf::Texture>> promise;
		std::future<std::vector<sf::Texture>> future;
		std::vector<std::promise<std::vector<sf::Texture>>> promiseTextures;
		std::vector< std::future<std::vector<sf::Texture>>> futureTextures;
		
		for (int i = 0; i < avaibleCores; i++) {
			std::cerr << "1";
			promiseTextures.push_back(std::move(promise));
			std::cerr << "2";
			futureTextures.push_back(std::move(promiseTextures[i].get_future()));
			std::cerr << "4";
		}
		
		std::vector<std::thread> threads;

		std::vector<int> borders;
		borders.push_back(0);
		for (int i = 1; i < avaibleCores; i++) {
			borders.push_back(allItemsNames.size() / avaibleCores * i);
			std::cerr << borders[i] << std::endl;
		}
		borders.push_back(allItemsNames.size());

		for (int i = 0; i < avaibleCores; i++) {
			threads.emplace_back(writeTextureAsThreadWithBorders, std::ref(promiseTextures[i]), borders[i], borders[i + 1]);
		}

		for (auto& thread : threads) {
			thread.join();
		}

		for (int i = 0; i < avaibleCores; i++) {
			allItemsTexture.insert(allItemsTexture.end(), futureTextures[i].get().begin(), futureTextures[i].get().end());
		}
	}
	catch (std::exception& e) {
		std::cerr << e.what();
	}*/

	
	

	writeAllItemsToVectors(allItemsNames, allItemsTexture);
	//writeTexturesToBinary(allItemsTexture);
	//writeAllItemsNames(allItemsNames);
	//allItemsTexture = readTexturesFromBinary();

	sf::Texture searchIconTexture;
	if (!searchIconTexture.loadFromFile("textures\\application\\search.png")) {
		std::cerr << "Search icon not load" << std::endl;
	}

	sf::Font textFont;
	if (!textFont.loadFromFile("fonts\\GalscBold.otf")) {
		std::cerr << "Font not load" << std::endl;
	}

	sf::Texture noneTexture;
	if (!noneTexture.loadFromFile("textures\\application\\none_texture.png")) {
		std::cerr << "None texture not load" << std::endl;
		return;
	}

	sf::Texture minecraftVanilaBack;
	if (!minecraftVanilaBack.loadFromFile("textures\\application\\grass_block_side.png")) {
		std::cerr << "Minecraft back not load" << std::endl;
	}
	sf::Texture returnToMenuTexture;
	if (!returnToMenuTexture.loadFromFile("textures\\application\\returnButton.png"))
	{
		std::cerr << "Return Button not load";
	}

	//rect with names & textures items
	std::vector<SFMLButton> buttonsInScrollMenu{};

	SFMLButton item1(330, 75, 30, SetColor("button"));
	item1.setOutline(SetColor("button_outline"), 4);
	item1.setPos(10, 60);
	//item1.setTexture(&minecraftVanilaBack);

	for (int i = 0; i < COUNT_BUTTONS_ON_SCROLL_MENU; ++i) {
		if (i > 0) {
			int index = i - 1;
			item1.setPos(buttonsInScrollMenu[index].getPos().x, buttonsInScrollMenu[index].getPos().y + buttonsInScrollMenu[index].getSize().y + DIST_BETWEEN_BUTTONS);
		}
		buttonsInScrollMenu.push_back(item1);
		
	}


	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	

	sf::RenderWindow creatorWindow(sf::VideoMode::getDesktopMode(), "Craft Creator", sf::Style::Fullscreen, settings);
	creatorWindow.setFramerateLimit(60);
	creatorWindow.setVerticalSyncEnabled(true);


	sf::RectangleShape searchRect(sf::Vector2f(370, 50));
	searchRect.setFillColor(SetColor("search_rect"));

	SFMLButton scrollBackgroundRect(350, sf::VideoMode::getDesktopMode().height-searchRect.getSize().y, 0, SetColor("scroll_background_rect"));
	scrollBackgroundRect.setPos(0, searchRect.getSize().y);

	SFMLButton scrollBorderLine(20,sf::VideoMode::getDesktopMode().height,0,SetColor("scroll_border_line"));
	scrollBorderLine.setPos(350,0);
	
	SFMLButton scrollButton(19.6, 35, 5, SetColor("button"));
	scrollButton.setPos(350.2, 50);

	SFMLButton returnToMenu(40, 20, 1, SetColor("button"));
	returnToMenu.setPos(1920 - returnToMenu.getSize().x, 0);
	//returnToMenu.setPos(1000, 900);

	sf::Sprite searchIcon(searchIconTexture);
	searchIcon.setScale(sf::Vector2f(0.1,0.1));
	
	//very important vars
	bool isScrollButtonActive = false;
	bool isScrolling = false;
	bool isMouseOnScrollButton = false;

	
	int allSlideCounter = allItemsNames.size() / 10;
	if (allItemsNames.size() % 10 != 0) {
		allSlideCounter += 1;
	}
	double stepScrollButoon = (sf::VideoMode::getDesktopMode().height - searchRect.getGlobalBounds().height - scrollButton.getSize().y) / allSlideCounter;

	std::vector<int> posScrollMenu{};
	for (int i = 0; i <= allSlideCounter; i++) {
		posScrollMenu.push_back(searchRect.getGlobalBounds().height + stepScrollButoon * i);
	}


	int counterItems = 0;
	

	double startItem = 0;
	while (creatorWindow.isOpen()) {

		sf::Event event;


		while (creatorWindow.pollEvent(event)){
			if (event.type == sf::Event::Closed) {
				creatorWindow.close();
			}

			if (returnToMenu.IsMouseOnButton(sf::Mouse::getPosition())) {

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					creatorWindow.close();
					menu();
				}
			}

			//scrolling with middle button
			if ((scrollBackgroundRect.IsMouseOnButton(sf::Mouse::getPosition()) || scrollBorderLine.IsMouseOnButton(sf::Mouse::getPosition()))
				&& event.type == sf::Event::MouseWheelScrolled) {

				isScrolling = true;

				double delta = event.mouseWheelScroll.delta * -1;
				if ((counterItems > 0 || delta > 0) && (counterItems < allSlideCounter - 1 || delta < 0)) {
					counterItems += delta;
				}
				

				scrollButton.setPos(scrollButton.getPos().x, posScrollMenu[counterItems]);
			}
			else {
				isScrolling = false;
			}

			//activation scroll buttton
			if (scrollButton.IsMouseOnButton(sf::Mouse::getPosition()) && event.type == event.MouseButtonPressed) {
					isScrollButtonActive = true;
			}

			if (event.type == event.MouseButtonReleased) {
				isScrollButtonActive = false;
			}

			if (isScrollButtonActive) {
				if (sf::Mouse::getPosition().y >= posScrollMenu[0] &&
					sf::Mouse::getPosition().y <= posScrollMenu[posScrollMenu.size() - 1]) {
					scrollButton.setPos(scrollButton.getPos().x, sf::Mouse::getPosition().y);
				}
				else if (sf::Mouse::getPosition().y < posScrollMenu[0]) {
					scrollButton.setPos(scrollButton.getPos().x, posScrollMenu[0]);
				}
				else {
					scrollButton.setPos(scrollButton.getPos().x, posScrollMenu[posScrollMenu.size() - 1]);
				}

				for (int i = 0; i < allSlideCounter; i++) {
					if (posScrollMenu[i] <= scrollButton.getPos().y && posScrollMenu[i + 1] > scrollButton.getPos().y) {
						counterItems = i;
						break;
					}
				}
			}

			if (isScrolling || isScrollButtonActive) {
				scrollButton.setColor(SetColor("button_shade"));
			}
			else {
				scrollButton.setColor(SetColor("button"));
			}


			startItem = counterItems * 10;

			
		}
		
		creatorWindow.clear(SetColor("background"));
		creatorWindow.draw(scrollBackgroundRect);
		creatorWindow.draw(scrollBorderLine);
		creatorWindow.draw(scrollButton);
		creatorWindow.draw(searchRect);
		creatorWindow.draw(searchIcon);

		returnToMenu.drawSprite(returnToMenuTexture, sf::Vector2f(0, 0),sf::Vector2f(0.05,0.05), creatorWindow);

		for (int i = 0; i < COUNT_BUTTONS_ON_SCROLL_MENU; ++i) {
			if (i + startItem < allItemsNames.size()) {
				buttonsInScrollMenu[i].DrawItem(allItemsTexture[i + startItem], allItemsNames[i + startItem], textFont, SetColor("text"), creatorWindow);
			}
		}

		
	

		creatorWindow.display();
		if (menuWindow.isOpen()) {
			menuWindow.close();
		}
		

	}

}