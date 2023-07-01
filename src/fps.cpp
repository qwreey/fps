#include "PowertoysFileLocksmith.h"
#include "pch.h"
#include "stringUtils.h"
#include "parseArguments.h"
#include "MatrixPretty.h"
#include "version.h"

using namespace std;

vector<string> formatFindResultItem(Filters filters,ProcessResult item) {
	int filterIndex = 0;
	vector<string> row;
	while (true) {
		Filter filter = filters.getFilter(filterIndex++);
		if (filter == Filter::none) break;
		else if (filter == Filter::name)     row.push_back(wstringToString(item.name));
		else if (filter == Filter::pid)      row.push_back(to_string(item.pid));
		else if (filter == Filter::user)     row.push_back(wstringToString(item.name));
		else if (filter == Filter::fullname) row.push_back(safePath(wstringToString(pid_to_full_path(item.pid))));
		else if (filter == Filter::files) {
			for (wstring file : item.files) {
				row.push_back(safePath(wstringToString(file)));
			}
		};
	}
	return row;
}

int main(int argc, char* argv[]) {
	// parse arguemtns into vector of string
	vector<string> arguments;
	int argIndex;
	for (argIndex = 1; argIndex < argc; argIndex++) {
		arguments.push_back( (string)argv[argIndex] );
	}

	// parse arguemtns with ProgramOptions
	ProgramOptions poptions;
	poptions.parse(arguments);

	if (poptions.showVersion) {
		cout << std::format("v{}\n", VERSION);
		return 0;
	}

	// check arguemtns is valid
	if (!poptions.isValid) {
		if (poptions.errorMessage.empty()) {
			cout << HelpMessage;
		} else {
			cerr << std::format("Error: commandline arguments parsing failed\n{}\nType '{} --help' to get more information", poptions.errorMessage, argv[0]);
		}
		return 2;
	}

	// convert path into wstring
	vector<ProcessResult> result = find_processes_recursive(poptions.files);

	// print result
	MatrixPretty output;
	if (!poptions.headless) {
		int filterIndex = 0;
		vector<string> heading;
		while (true) {
			Filter filter = poptions.filters.getFilter(filterIndex++);
			if (filter == Filter::none) break;
			else if (filter == Filter::pid)      heading.push_back("PID");
			else if (filter == Filter::name)     heading.push_back("ImageName");
			else if (filter == Filter::user)     heading.push_back("User");
			else if (filter == Filter::fullname) heading.push_back("Path");
			else if (filter == Filter::files)    heading.push_back("OpenFiles");
		}
		output.pushRow(heading);
	}
	for (ProcessResult item : result) {
		output.pushRow(formatFindResultItem(poptions.filters,item));
	}
	cout << output.format(poptions.outputFormat == OutputFormats::csv ? FormatTypes::Csv : FormatTypes::Table);
	if (poptions.count) cout << result.size() << "\n";
	return (int)result.empty();
}
