#pragma once
#include "pch.cpp"

std::wstring stringToWstring(const std::string& str);

std::string wstringToString(const std::wstring& wstr);

std::vector<std::string> split(std::string str, char splitter);

std::string safePath(std::string path);
