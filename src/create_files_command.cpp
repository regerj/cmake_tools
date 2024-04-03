#include "create_files_command.h"

#include "enums.h"
#include "utils.h"

#include <fstream>
#include <regex>
#include <sstream>
#include <string>

command_status create_files(std::string &name) {
    // Create source file
    auto status = create_file(name + ".cpp", "#include \"" + name + ".h\"");
    if (status.is_error()) {
        return status;
    }

    // Create header file
    status = create_file(name + ".h", "#pragma once");
    if (status.is_error()) {
        return status;
    }

    // Read the contents of the cmakelists.txt
    std::fstream local_cmakelists;
    local_cmakelists.open("CMakeLists.txt");
    std::stringstream ss;
    ss << local_cmakelists.rdbuf();
    std::string file_contents = ss.str();

    // Insert the new file name
    std::regex pattern("target_sources\\([^\\)]*");
    std::string text_to_insert = "    " + name + ".cpp\n";
    status = insert(file_contents, pattern, text_to_insert);
    if (status.is_error()) {
        return status;
    }

    // Print back to the file
    local_cmakelists.close();
    local_cmakelists.open("CMakeLists.txt", std::fstream::out | std::fstream::trunc);
    local_cmakelists << file_contents;
    local_cmakelists.close();

    return COMMAND_SUCCESS;
}
