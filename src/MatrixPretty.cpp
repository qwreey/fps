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

string replace_all(
	std::string& s,
	std::string const& toReplace,
	std::string const& replaceWith
) {
	std::string buf;
	std::size_t pos = 0;
	std::size_t prevPos;

	// Reserves rough estimate of final size of string.
	buf.reserve(s.size());

	while (true) {
		prevPos = pos;
		pos = s.find(toReplace, pos);
		if (pos == std::string::npos)
			break;
		buf.append(s, prevPos, pos - prevPos);
		buf += replaceWith;
		pos += toReplace.size();
	}

	buf.append(s, prevPos, s.size() - prevPos);
	return buf;
}

string escapeCsvValue(string value) {
	if (value.find_first_of("\"") == string::npos && value.find_first_of(",") == string::npos) return value;
	return "\"" + replace_all(value,"\"", "\"\"") + "\"";
}

string MatrixPretty::format(FormatTypes type) {
	string output = "";

	switch (type) {
	case FormatTypes::Csv:
		for (vector<string> row : matrix) {
			int maxIndex = row.size();
			for (int index = 0; index < maxIndex; index++) {
				output.append(escapeCsvValue(row[index]));
				if (index != maxIndex-1) output.append(",");
			}
			output.append("\n");
		}
		break;
	case FormatTypes::Table:
	default:
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
				if (calIndex != calLength - 1) {
					string spaces(calsizes[calIndex] - sizeToInt(item.length()) + 1, ' ');
					output.append(spaces);
				}
			}
			output.append("\n");
		}
		break;
	}

	return output;
}
