#pragma once
#include "pch.h"

enum FormatTypes
{
	Csv,
	Table
	// TODO : json
};

class MatrixPretty {
private:
	std::vector<int> calsizes;

public:
	std::vector<std::vector<std::string>> matrix;

	void pushRow(std::vector<std::string> row);
	std::string format(FormatTypes type);
};
