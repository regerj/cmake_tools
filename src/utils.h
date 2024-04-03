#pragma once

#include "enums.h"

#include <regex>
#include <string>

command_status create_file(std::string name, std::string content = std::string());

command_status get_first_of(std::string &find, std::regex &pattern, std::string &output);

command_status insert(std::string &find, std::regex &pattern, std::string &insert);
