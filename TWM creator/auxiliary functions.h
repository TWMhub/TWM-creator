#pragma once
#include "SFML/Graphics.hpp"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include <fstream>
#include <iostream>
#include <string>
#include <locale>
#include <filesystem>
#include <thread>
#include <mutex>
#include <future>


//it for threads
//void writeTextureAsThreadWithBorders(std::promise<std::vector<sf::Texture>>& promiseTextures, int topBorder, int lowBorder) {
//	std::vector<sf::Texture> textures;
//
//	const std::string pathToItems = "textures\\creator\\icons\\minecraft";
//	int i = 0;
//	sf::Texture iterableTexture;
//
//	try {
//		for (const auto& entity : std::filesystem::directory_iterator(pathToItems)) {
//			auto fileName = entity.path().filename().string();
//			if (i >= topBorder && i < lowBorder) {
//
//				if (!iterableTexture.loadFromFile(pathToItems + "\\" + fileName)) {
//					std::cerr << "Search icon not load";
//				}
//				else {
//					textures.push_back(iterableTexture);
//				}
//			}
//			if (i >= lowBorder) {
//				break;
//			}
//		}
//	}
//	catch (const std::filesystem::filesystem_error& e) {
//		std::cerr << e.what() << std::endl;
//	}
//
//	promiseTextures.set_value(std::move(textures));
//}



void replaceSecondSpaceWithNewline(std::string& input) {
	int spaceCount = 0;
	std::string output = input;

	for (size_t i = 0; i < output.length(); ++i) {
		if (output[i] == ' ') {
			++spaceCount;
			if (spaceCount == 2) {

				output[i] = '\n';
				break;
			}
		}
	}

	input = output;
}

void writeAllItemsNames(std::vector<std::string>& allItemsNames) {
	const std::string pathToItems = "textures\\creator\\icons\\minecraft";

	try {
		for (const auto& entity : std::filesystem::directory_iterator(pathToItems)) {

			auto fileName = entity.path().filename().string();
			auto fileNameNew = fileName.substr(0, fileName.find_last_of('.'));
			std::replace(fileNameNew.begin(), fileNameNew.end(), '_', ' ');

			if (fileNameNew.length() > 25) {
				replaceSecondSpaceWithNewline(fileNameNew);
			}

			//std::cerr << fileNameNew << std::endl;
			  
			allItemsNames.push_back(fileNameNew);

		}
	}
	catch (const std::filesystem::filesystem_error& e) {
		std::cerr << e.what() << std::endl;
	}
}


void writeAllItemsToVectors(std::vector<std::string>& itemsNames,std::vector<sf::Texture>& itemsSprites) {

	//TODO finish importing items from a folder
	std::cerr << "And now wait, I still don\'t understand how to work with multithreading." << std::endl;

	const std::string pathToItems = "textures\\creator\\icons\\minecraft";
	int i = 0;
	sf::Texture iterableTexture;
	
	try {
		for (const auto& entity : std::filesystem::directory_iterator(pathToItems)) {
			auto fileName = entity.path().filename().string();
			auto fileNameNew = fileName.substr(0, fileName.find_last_of('.'));
			std::replace(fileNameNew.begin(), fileNameNew.end(), '_', ' ');
			if (fileNameNew.length() > 25) {
				replaceSecondSpaceWithNewline(fileNameNew);
			}

			//std::cerr << fileNameNew << std::endl;

			itemsNames.push_back(fileNameNew);
			

			if (!iterableTexture.loadFromFile(pathToItems + "\\" + fileName)) {
				std::cerr << "Search icon not load";
			}
			else {
				itemsSprites.push_back(iterableTexture);
			}
		}
	}
	catch (const std::filesystem::filesystem_error& e) {
		std::cerr << e.what() << std::endl;
	}


}



void setTextShadow(sf::Text& text,sf::Color shadowColor) {
	text.setFillColor(shadowColor);
	text.move(6, 5);

}

void removeTextShadow(sf::Text& text, sf::Color textColor) {
	text.setFillColor(textColor);
	text.move(-6, -5);
}	

std::string get—urrentPath() {
	return std::filesystem::current_path().string();
}

std::string shorteningTheString(const std::string& path) {
	const size_t MaxLength = 40;
	const size_t EdgeLength = 20; // ƒÎËÌ‡ Ì‡˜‡Î¸ÌÓÈ Ë ÍÓÌÂ˜ÌÓÈ ˜‡ÒÚË ÒÚÓÍË
	if (path.length() > MaxLength) {
		if (path.length() > 2 * EdgeLength + 3) {
			std::string shortenedPath = path.substr(0, EdgeLength) + "..." +
				path.substr(path.length() - EdgeLength);
			return shortenedPath;
		}
		else {
			return path;
		}
	}
	else {
		return path;
	}
}


void setNewPath(std::string nameOfPath, std::string namePath) {
	std::string path = get—urrentPath() + "\\settings.json";
	std::ifstream file(path);

	if (!file.is_open()) {
		std::cerr << "programm cant open JSON" << std::endl;
	}
	std::string jsonString((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	file.close();

	rapidjson::Document doc;
	doc.Parse(jsonString.c_str());


	if (doc.HasMember(nameOfPath.c_str())) {
		doc[nameOfPath.c_str()].SetString(namePath.c_str(), doc.GetAllocator());
	}
	std::ofstream outputFile(path);
	rapidjson::StringBuffer buffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);
	outputFile << buffer.GetString();
	outputFile.close();
}

std::string checkingForPresenceOfPath(std::string nameOfPath) {
	std::string path = get—urrentPath() + "\\settings.json";
	std::ifstream file(path);

	if (!file.is_open()) {
		std::cerr << "programm cant open JSON" << std::endl;
	}
	std::string jsonString((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	file.close();

	rapidjson::Document doc;
	doc.Parse(jsonString.c_str());

	if (doc.HasMember(nameOfPath.c_str())) {
		return doc[nameOfPath.c_str()].GetString();
	}

	return "a";
}

std::string chekVersion() {
	std::string path = get—urrentPath() + "\\settings.json";
	std::ifstream file(path);
	std::string jsonTableName = "version";
	if (!file.is_open()) {
		std::cerr << "programm cant open JSON" << std::endl;
	}
	std::string jsonString((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	file.close();

	rapidjson::Document doc;
	doc.Parse(jsonString.c_str());

	if (doc.HasMember(jsonTableName.c_str())) {
		return doc[jsonTableName.c_str()].GetString();
	}

	return "a";
}

bool isPathsEmpty() {
	if (checkingForPresenceOfPath("path_to_crafts") == "" || checkingForPresenceOfPath("path_to_src_icons_from_mod") == "") {
		return true;
	}
	else {
		return false;
	}
}