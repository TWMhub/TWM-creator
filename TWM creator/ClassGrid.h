#pragma once
#include <vector>
#include <iostream>
#include <string>

class Grid
{
protected:

	void getGrid();
private:
	struct GridStruct
	{
		std::vector<std::vector<std::string>> ñraftGridItems;
		std::string outputCraft = NULL;
		std::string auxiliaryCraftItem = NULL;
	};
};

