#pragma once
#include "ClassButton.h"
#include "SFML/Graphics.hpp"

class customText {
public:
	customText(sf::Font font, std::string text, sf::Vector2f pos, int chapterSize, sf::Color color) :
		font(font), pos(pos), text(text), color(color), chapterSize(chapterSize) {
		build();
	}

	void setPos(sf::Vector2f pos) {
		sfmlText.setPosition(pos);
	}

	void setPosByButton(SFMLButton button) {
		sf::Vector2f posText{ button.getPos().x + button.getSize().x / 2 - sfmlText.getGlobalBounds().width / 2, button.getPos().y + button.getSize().y / 2 - sfmlText.getGlobalBounds().height / 2 };
		sfmlText.setPosition(posText);
	}

	void move(sf::Vector2f move) {
		sfmlText.move(move);
	}

	void setText(std::string text) {
		sfmlText.setString(text);
	}

	void build() {
		sfmlText.setString(text);
		sfmlText.setFont(font);
		sfmlText.setCharacterSize(chapterSize);
		sfmlText.setFillColor(color);
		sfmlText.setPosition(pos);
	}

	sf::Text getText() {
		return sfmlText;
	}

private:
	sf::Font font;
	sf::Vector2f pos;
	int chapterSize;
	sf::Color color;
	std::string text;
	sf::Text sfmlText;
};