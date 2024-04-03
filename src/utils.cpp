#include "enums.h"
#include "utils.h"

#include <cstdio>
#include <fstream>
#include <regex>
#include <string>

command_status create_file(std::string name, std::string content) {
    std::ofstream output_file;
    output_file.open(name);
    output_file << content;
    output_file.close();

    return COMMAND_SUCCESS;
}

command_status get_first_of(std::string &find, std::regex &pattern, std::string &output) {
    std::smatch found;
    if (!std::regex_search(find, found, pattern)) {
        return COMMAND_NO_MATCH;
    }

    output = found.str();
    return COMMAND_SUCCESS;
}

command_status insert(std::string &find, std::regex &pattern, std::string &insert) {
    std::smatch found;
    if (!std::regex_search(find, found, pattern)) {
        printf("Failed to insert\n");
        return COMMAND_NO_MATCH;
    }

    // This is stupid, and I hate it, but \K does not work in C++ std::regex because
    // fuck me I guess
    find.insert(found.position() + found.length(), insert);

    return COMMAND_SUCCESS;
}
