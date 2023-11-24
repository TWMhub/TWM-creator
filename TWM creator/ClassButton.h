#pragma once
#include <cmath>
#include <iostream>
#include "SFML/Graphics.hpp"
#define PI 3.14159265
#define auxiliary_functions_h


class SFMLButton :public sf::Drawable, sf::Transformable {
public:

	SFMLButton() :height(10), lenght(20) {
		build();
	};

	SFMLButton(double lenght, double height, double angle, double posX, double posY, sf::Color color) :
		height(height), lenght(lenght), posX(posX), posY(posY), color(color) {
		Button.setPosition(posX, posY);
		Button.setFillColor(color);
		radBevel = ApplyButtonBevel(angle);
		build();
	};
	//женя лох
	SFMLButton(double lenght, double height, double angle, sf::Color color) :
		height(height), lenght(lenght), color(color) {
		Button.setFillColor(color);
		radBevel = ApplyButtonBevel(angle);
		build();
	};

	void setPos(double x, double y) {
		Button.setPosition(sf::Vector2f(x, y));
		build();
	}

	void setAngle(double angle) {
		radBevel = ApplyButtonBevel(angle);
		build();
	}

	void setSize(double x, double y) {
		lenght = x;
		height = y;
		radBevel = ApplyButtonBevel(radBevel);
		build();
	}

	void setColor(sf::Color color) {
		Button.setFillColor(color);
		this->color = color;
	}
	sf::Vector2f getSize() {
		return sf::Vector2f(lenght, height);
	}

	sf::Vector2f getPos() {
		return Button.getPosition();
	}

	sf::Vector2f getPosForText(sf::Text text) {
		return sf::Vector2f(Button.getPosition().x + Button.getGlobalBounds().width / 2 - text.getGlobalBounds().width / 2,
			Button.getPosition().y + height / 2 - text.getGlobalBounds().height / 2);
	}
	bool IsMouseOnButton(sf::Vector2i pos) {
		if (pos.x > Button.getGlobalBounds().left && pos.x < Button.getGlobalBounds().left + Button.getLocalBounds().width) {
			if (pos.y > Button.getGlobalBounds().top && pos.y < Button.getGlobalBounds().top + Button.getLocalBounds().height) {
				return true;
			}
		}
		return false;
	}

	void setOutline(sf::Color color, double outlineSize) {
		Button.setOutlineColor(color);
		Button.setOutlineThickness(outlineSize);
	}

	bool chekBorder(sf::Vector2i mousePos, double topBorder, double lowerBorder) {
		return mousePos.y > topBorder + height / 2 && mousePos.y < lowerBorder - height / 2;
	}


	double simulationScrollByMouse(sf::Vector2i mousePos,double topBorder,double lowerBorder, int counterItems) {
		if(chekBorder(mousePos,topBorder,lowerBorder)) {
			Button.setPosition(sf::Vector2f(Button.getPosition().x, mousePos.y - height / 2));
			return (mousePos.y - topBorder) / ((lowerBorder - topBorder) / counterItems ) ;
		}
	}

	void move(double x,double y) {
		Button.move(x, y);
	}

	void DrawItem(const sf::Texture& itemTexture,const std::string& nameItem, const sf::Font& font,const sf::Color& colorText, sf::RenderWindow& window) {
		sf::Sprite itemSptite(itemTexture);
		itemSptite.setPosition(sf::Vector2f(posX + 22, getPos().y + getSize().y/2 - itemSptite.getGlobalBounds().height / 2));

		sf::Text itemName;
		itemName.setString(nameItem);
		itemName.setFillColor(colorText);
		itemName.setFont(font);
		itemName.setCharacterSize(20);
		itemName.setPosition(itemSptite.getGlobalBounds().left + itemSptite.getGlobalBounds().width + 10, getPos().y + getSize().y / 2 - itemName.getLocalBounds().height / 2);

		window.draw(Button);
		window.draw(itemSptite);
		window.draw(itemName);
	}

	void drawSprite(const sf::Texture& itemTesxture, sf::Vector2f SpritePos0XY, sf::RenderWindow& Window){
		sf::Sprite itemSprite(itemTesxture);
		sf::Vector2f posSprite = sf::Vector2f(Button.getPosition().x + (itemSprite.getGlobalBounds().width/2), Button.getPosition().y + itemSprite.getGlobalBounds().);
		itemSprite.setPosition(sf::Vector2f())
	}

	void setTexture(const sf::Texture* background) {
		
		Button.setTexture(background);
		Button.setTextureRect(sf::IntRect(0, 0, 16, 16));
	}

	void setCenterByWindowByX(const sf::RenderWindow& window, double posY) {
		double centerWindow =/* window.getPosition().x +*/ window.getSize().x / 2;
		setPos((centerWindow - getSize().x / 2), posY);
		build();
	}


private:

	void build() {
		Button.setPointCount(60);
		double helpX = 0, helpY = 0, stepDeg = 90 / (Button.getPointCount() / 4 -1), degrees=270;

		sf::Vector2f CenterAxis[4] = {
			sf::Vector2f(posX + lenght - radBevel, posY + radBevel),
			sf::Vector2f(posX + lenght - radBevel, posY + height - radBevel),
			sf::Vector2f(posX + radBevel, posY + height - radBevel),
			sf::Vector2f(posX + radBevel, posY + radBevel)
		};
		int PointADD = 15;

		for (int NumberAngel = 0; NumberAngel < 4; NumberAngel++) {
			//double degrees = degreesArray[NumberAngel];
			PointADD = 15 * NumberAngel;
			for (int i = 0; i < 15; i++) {
				degrees += stepDeg;
				helpX = radBevel * cos(DegreesToRadians(degrees)) + CenterAxis[NumberAngel].x;
				helpY = radBevel * sin(DegreesToRadians(degrees)) + CenterAxis[NumberAngel].y;
				Button.setPoint(i + PointADD, sf::Vector2f(helpX, helpY));
			
			}
		}
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(Button);
		states.transform *= getTransform();
	}

	double DegreesToRadians(double degrees) {
		return degrees * PI / 180;
	}

	double ApplyButtonBevel(double userRadBevel) {
		if (userRadBevel <= std::min(height / 2, lenght / 2)) {
			return userRadBevel;
		}
		else {
			return std::min(height / 2, lenght / 2);
		}

	}


	sf::ConvexShape Button;
	sf::Vector2f moveShadow = sf::Vector2f(0, 0);
	sf::Color color = sf::Color::Red;
	sf::Color shadowColor = sf::Color::Black;

	double height = 0;
	double lenght = 0;
	double radBevel = 0;
	double posX = 0;
	double posY = 0;
};