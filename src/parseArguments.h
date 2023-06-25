#pragma once
#include "pch.h"

enum Filter {
	none = -1,
	name,
	fullname,
	user,
	pid,
	files
};

class Filters {
public:
	bool changed = false; // if not chaged, using default option
	int position = 0; // current position

	// Each elements mean position of itself
	int name = -1; // Program image name
	int fullname = -1; // Program image path
	int user = -1; // User name
	int pid = -1; // Process id
	int files = -1; // files

	void all();
	void init();
	void usingDefault();
	Filter getFilter(int index);

	Filters() = default;
};

class ProgramOptions {
private:
	bool parseFilter(std::string argument);
	bool parseOption(std::string option);
	int parsePos = 0;

public:
	void parse(std::vector<std::string> argumentList);

	// output
	bool isValid = true;
	std::string errorMessage = "";
	std::vector<std::wstring> files;
	Filters filters;
	bool headless = false;
	bool verbose = false;
	bool showVersion = false;
	bool count = false;

	ProgramOptions() = default;
};

const std::string HelpMessage =
	"Usage:   fps [-HA] [-f pid,image,...] ...[<File|Directory>]\n"
	"Defualt: fps -f \"pid,image,user\" .\n"
	"\n"
	"Report processes which using specific file or directory.\n"
	"If filter option not given, prints pid, name and user as default.\n"
	"The output order of each element follows the order of the given options.\n"
	"Options can be combined into a single argument like 'fps -HA'\n"
	"example: fps -f \"pid,image\" .\n"
	"\n"
	"General options\n"
	" -h, --help, -?  Show this messages.\n"
	" -H, --headless  Print results without heading.\n"
	" -a, --all       Use all filter options, output order follows the order of help.\n"
	" -f, --filter [filter,filter,...]\n"
	"                 Use filters to show. see 'Filter options'\n"
	" -v, --version   Show version of fps\n"
	" -V, --verbose   Verbose mode for debugging (Not used for now)\n"
	" -c  --count     Count number of processes and print it as last line\n"
	"\n"
	"Filter options\n"
	" pid    PID of found process.\n"
	" image  Image name of found process.\n"
	"        This is the executable file name rather than the full path.\n"
	" user   Username of who the found process runs.\n"
	" path   Full path of found process\n"
	" files  Full paths of files which found process uses.\n"
	"\n"
	"Exit status:\n"
	" 0: if found processes\n"
	" 1: if has no processes\n"
	" 2: commandline arguments is invalid\n";
