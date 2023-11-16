#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#define PI 3.14159265     

class CustomButton : public sf::Drawable, sf::Transformable {
public:

	CustomButton() { // пустой конструктор 
		x = 0;
		y = 0;
		angle = 0;
	};

	CustomButton(float x, float y, float ang, sf::Color color) { // конструктор только для размеров
		this->x = x;
		this->y = y;
		this->angle = ang;
		Button.setFillColor(color);
		SetButton();
	}

	CustomButton(float x, float y, float ang, float PosX, float PosY, sf::Color color) { // конструктор всех характеристик
		this->x = x;
		this->y = y;
		this->angle = ang;
		Button.setFillColor(color);
		Button.setPosition(sf::Vector2f(PosX,PosY));
		SetButton();
	}

	void setAng(float angle) { // устанавливает радиус сглаживания угла
		this->angle = angle;
		SetButton();
	}

	void setSize(float x,float y) { // устанавливает размер 

		this->x = x;
		this->y = y;
		SetButton();
	}

	void setPos(float x,float y) {
		Button.setPosition(sf::Vector2f(x,y));
	}

	void setColor(sf::Color color) {
		Button.setFillColor(color);
	}

	sf::Vector2f getSize(){
		return sf::Vector2f(x, y);
	}

	sf::Vector2f getPos() {
		return Button.getPosition();
	}

	sf::Vector2f getPosForText(sf::Text text) {
		return sf::Vector2f(Button.getGlobalBounds().left + Button.getLocalBounds().width / 2 - text.getLocalBounds().width / 2,
			Button.getGlobalBounds().top + Button.getLocalBounds().height / 2 - text.getLocalBounds().height / 2);
	}

	bool isPosInButton(sf::Vector2f pos) {
		if (pos.x > Button.getGlobalBounds().left && pos.x < Button.getGlobalBounds().left + Button.getGlobalBounds().width) {
			if (pos.y > Button.getGlobalBounds().top && pos.y < Button.getGlobalBounds().top + Button.getGlobalBounds().height) {
				return true;
			}
		}
		return false;
	}

	bool isPosInButton(sf::Vector2i pos) {
		if (pos.x > Button.getGlobalBounds().left && pos.x < Button.getGlobalBounds().left + Button.getGlobalBounds().width) {
			if (pos.y > Button.getGlobalBounds().top && pos.y < Button.getGlobalBounds().top + Button.getGlobalBounds().height) {
				return true;
			}
		}
		return false;
	}

	

	/*void setOutcolor(float outline, sf::Color color) {  // не работает адекватно
		Button.setOutlineThickness(outline);
		Button.setOutlineColor(color);
		
	}*/
	

private:

	void SetButton() {
		
		float ratio = x / y;
		float step = 90 / 15;

		ChekAngle();

		Button.setPointCount(80);

		Button.setPoint(0, sf::Vector2f(angle, 0));
		Button.setPoint(1, sf::Vector2f(x - angle, 0));

		float degree = 90;
		float x0 = x - angle;
		float y0 = angle;
		for (int i = 2; i < Button.getPointCount()/4; i++) {
			degree -= step;
			Button.setPoint(i, sf::Vector2f(SetX(degree) + x0, SetY(degree) + y0));
			
		}
		
		Button.setPoint(Button.getPointCount() / 4, sf::Vector2f(x, angle));
		Button.setPoint(Button.getPointCount() / 4 + 1, sf::Vector2f(x, y - angle));

		degree = 360;
		x0 = x - angle;
		y0 = y - angle;
		for (int i = Button.getPointCount() / 4 + 2; i < Button.getPointCount() / 2; i++) {
			degree -= step;
			Button.setPoint(i, sf::Vector2f(-SetX(degree) + x0, -SetY(degree) + y0));
		}

		Button.setPoint(Button.getPointCount() / 2, sf::Vector2f(x - angle, y));
		Button.setPoint(Button.getPointCount() / 2 + 1, sf::Vector2f(angle, y));

		degree = 270;
		x0 = angle;
		y0 = y - angle;
		for (int i = Button.getPointCount() / 2 + 2; i < Button.getPointCount() / 4 * 3; i++) {
			degree -= step;
			Button.setPoint(i, sf::Vector2f(SetX(degree) + x0, SetY(degree) + y0));
		}

		Button.setPoint(Button.getPointCount() / 4 * 3, sf::Vector2f(0, y - angle));
		Button.setPoint(Button.getPointCount() / 4 * 3 + 1, sf::Vector2f(0, angle));

		degree = 180;
		x0 = angle;
		y0 = angle;
		for (int i = Button.getPointCount() / 4 * 3 + 2; i < Button.getPointCount(); i++) {
			degree -= step;
			Button.setPoint(i, sf::Vector2f(-SetX(degree) + x0, SetY(degree) + y0));
		}

	}

	
	


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {

		states.transform *= getTransform();
		target.draw(Button);
	}

	float SetX(float degree) {
		return  angle * cos(degree);
	}

	float SetY(float degree) {
		return  angle * sin(degree);
	}

	void ChekAngle() { 
		float x1 = this->x / 2, y1 = this->y / 2;
		if (angle <= x1 && angle <= y1) {
			this->angle = angle;
		}
		else {
			this->angle = std::min(x1, y1);
		}

	}


	sf::ConvexShape Button;

	float angle;
	float x;
	float y;
};


