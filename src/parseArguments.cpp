#include "parseArguments.h"
#include "stringUtils.h"

using namespace std;

Filter Filters::getFilter(int index) {
	if (name == index)     return Filter::name;
	if (fullname == index) return Filter::fullname;
	if (user == index)     return Filter::user;
	if (pid == index)      return Filter::pid;
	if (files == index)    return Filter::files;
	return Filter::none;
}

void Filters::usingDefault() {
	pid = 0;
	fullname = -1;
	user = 2;
	name = 1;
	files = -1;
}

void Filters::init() {
	pid = -1;
	fullname = -1;
	user = -1;
	name = -1;
	files = -1;
	changed = true;
	position = 0;
}

void Filters::all() {
	pid = 0;
	fullname = 3;
	user = 2;
	name = 1;
	files = 4;
	changed = true;
	position = 5;
}

bool ProgramOptions::parseFilter(string argument) {
	if (filters.changed) {
		isValid = false;
		errorMessage += "Filters are already set. Combinations between filters must use ','\n";
		return false;
	}
	filters.init();
	for (string filterName : split(argument, ',')) {
		if (filterName == "pid")        filters.pid      = filters.position++;
		else if (filterName == "image") filters.name     = filters.position++;
		else if (filterName == "user")  filters.user     = filters.position++;
		else if (filterName == "path")  filters.fullname = filters.position++;
		else if (filterName == "files") filters.files    = filters.position++;
	}
	if (filters.position == 0) {
		isValid = false;
		errorMessage += "Filter is empty.\n";
	}
	return false;
}

bool ProgramOptions::parseOption(string option) {
	if (option == "headless" || option == "H") {
		headless = true;
	}
	else if (option == "count") {
		count = true;
	}
	else if (option == "all" || option == "a") {
		filters.all();
	}
	else if (option == "help" || option == "?" || option == "h") {
		isValid = false;
		errorMessage = "";
		return true;
	}
	else if (option == "f") {
		isValid = false;
		errorMessage += "Filter option -f cannot be combined with another general options.\n";
	}
	else if (option == "verbose") {
		verbose = true;
	}
	else if (option == "version" || option == "v") {
		showVersion = true;
	}
	else if (option == "csv" || option == "c") {
		outputFormat = OutputFormats::csv;
	}
	else {
		isValid = false;
		errorMessage += format("'{}' is invalid option.\n", option);
	}
	return false;
}

void ProgramOptions::parse(vector<string> argumentList) {
	errorMessage = "";
	isValid = true;
	for (parsePos = 0; parsePos < argumentList.size(); (parsePos)++) {
		string argument = argumentList[parsePos];

		// filter options
		if (argument == "--filter" || argument == "-f") {
			if (argumentList.size() <= parsePos) {
				isValid = false;
				errorMessage += format("{} requires [filter,...] option.", argument);
				return;
			}
			if (parseFilter(argumentList[++parsePos])) return;
		// escape argument (file)
		} else if (argument.starts_with("\\-")) {
			files.push_back(stringToWstring(argument.substr(1, argument.length() - 1)));
		// general options
		} else if (argument.starts_with("--")) {
			if (parseOption(argument.substr(2, argument.length() - 1))) return;
		} else if (argument.starts_with("-")) {
			for (char option : argument.substr(1, argument.length() - 1)) {
				string optionStr(1, option);
				if (parseOption(optionStr)) return;
			}
		// file
		} else {
			files.push_back(stringToWstring(argument));
		}
	}

	// default filter if has no filters
	if (!filters.changed) filters.usingDefault();

	// use cwd if has no files
	if (files.empty()) files.push_back(L".");
}
