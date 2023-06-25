#include "pch.h"
#include "MatrixPretty.h"

using namespace std;

int sizeToInt(size_t size) {
	return static_cast<int>(size);
}

void MatrixPretty::pushRow(vector<string> row) {
	int index;
	for (index = 0; index < sizeToInt(row.size()); index++) {
		int size = sizeToInt(row[index].length());
		if (sizeToInt(calsizes.size()) <= index) calsizes.push_back(size);
		else calsizes[index] = max<int>(calsizes[index],size);
	}
	matrix.push_back(row);
}

std::string MatrixPretty::format() {
	string output = "";
	int calIndex;
	int rowIndex;
	int rowLength = sizeToInt(matrix.size());
	int calLength;

	for (rowIndex = 0; rowIndex < rowLength; rowIndex++) {
		vector<string> row = matrix[rowIndex];
		calLength = sizeToInt(row.size());
		for (calIndex = 0; calIndex < calLength; calIndex++) {
			string item = row[calIndex];
			output.append(item);
			if (calIndex != calLength -1) {
				string spaces(calsizes[calIndex] - sizeToInt(item.length()) + 1, ' ');
				output.append(spaces);
			}
		}
		output.append("\n");
	}

	return output;
}
