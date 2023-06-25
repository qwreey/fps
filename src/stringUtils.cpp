#include "pch.h"
#include "stringUtils.h"

using namespace std;

wstring stringToWstring(const string& str) {
	wstring result(str.begin(), str.end());
	return result;
}

string wstringToString(const wstring& wstr) {
	string result(wstr.begin(), wstr.end());
	return result;
}

vector<string> split(string str, char splitter) {
	vector<string> result;
	string buffer = "";
	for (char item : str) {
		if (item == splitter) {
			result.push_back(buffer);
			buffer = "";
		}
		else {
			buffer += item;
		}
	}
	if (!buffer.empty()) result.push_back(buffer);
	return result;
}

string safePath(string path) {
	if (path.find(' ') == string::npos) {
		return path;
	}
	return format("\"{}\"", path);
}
