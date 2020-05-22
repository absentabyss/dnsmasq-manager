#ifndef SHELL_H
#define SHELL_H

#include <string>

std::string exec(const char* cmd);

// Systemd dependent.
bool unitIsHealthy(const std::string &unit);
void refreshUnit(const std::string &unit);

#endif
