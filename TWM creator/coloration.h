#pragma once
#include <string>
#include <cctype>
#include <fstream>
#define RAPIDJSON_DOCUMENT_H_INCLUDED
#define auxiliary_functions_h
#include "SFML/Graphics.hpp"

std::string getСurrentPath() {
	return std::filesystem::current_path().string();
}

std::string getColorFromJson(std::string nameColor) {

	std::string name = getСurrentPath() + "\\settings.json";
	std::ifstream file(name);

	if (!file.is_open()) {
		std::cerr << "programm cant open JSON" << std::endl;
	}
	std::string jsonString((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	file.close();
	
	rapidjson::Document doc;
	doc.Parse(jsonString.c_str());

	if (doc.HasMember("color palette")) {
		const rapidjson::Value& colors = doc["color palette"];

		if (colors.HasMember(nameColor.c_str())) {
			std::string color = colors[nameColor.c_str()].GetString();
			return color;
		
		}
		else {
			std::cerr << "Color not found";
		}
	}


	
	return "#000000";
}

int HexToInt(char a) {
	if (a >= '0' && a <= '9') {
		return a - '0';
	}
	else if (a >= 'A' && a <= 'F') {
		return a - 'A' + 10;
	}
	else if (a >= 'a' && a <= 'f') {
		return a - 'a' + 10;
	}
	else {
		return -1;
	}
}


sf::Color SetColor(std::string col) { // ��������� �������� ����� ����� ���� �� sfml
	std::string color = getColorFromJson(col);
	if (color.length() != 7) {
		std::cerr << color.length();
		return sf::Color::Red;
	}
	int a1, a2, a3;
	a1 = (HexToInt(color[1]) * 16) + HexToInt(color[2]);
	a2 = (HexToInt(color[3]) * 16) + HexToInt(color[4]);
	a3 = (HexToInt(color[5]) * 16) + HexToInt(color[6]);
	
	sf::Color a(a1, a2, a3);
	return a;
}

sf::Color SetColor(std::string col, float alphaColor) { // ��������� �������� ����� ����� ���� �� sfml
	std::string color = getColorFromJson(col);
	if (color.length() != 7) {
		std::cerr << color.length();
		return sf::Color::Red;
	}
	int a1, a2, a3;
	a1 = (HexToInt(color[1]) * 16) + HexToInt(color[2]);
	a2 = (HexToInt(color[3]) * 16) + HexToInt(color[4]);
	a3 = (HexToInt(color[5]) * 16) + HexToInt(color[6]);
	
	if (alphaColor < 0) {
		alphaColor = 0;
	}

	if (alphaColor > 254) {
		alphaColor = 255;
	}

	sf::Color a(a1, a2, a3,alphaColor);
	return a;
}

