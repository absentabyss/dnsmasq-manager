#include "shell.h"

#include <array>
#include <cstdio>
#include <iostream>
#include <memory>
#include <regex>
#include <stdexcept>
#include <unistd.h>

// Thanks to waqas and gregpaton08
// https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

bool unitIsHealthy(const std::string &unit)
{
	std::string command{ "systemctl status " };
	command += unit + " | grep Active";
	std::string unitStatus{ exec(command.c_str()) };
	std::regex re{ "failed" };
	return !std::regex_search(unitStatus.c_str(), re);
}

void refreshUnit(const std::string &unit)
{
	std::string command{ "systemctl restart " };
	command += unit;
	std::system(command.c_str());
	return;
}
