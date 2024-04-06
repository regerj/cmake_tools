#include "bootstrap_command.h"
#include "command_execute.h"
#include "enums.h"
#include "utils.h"

#include <filesystem>
#include <format>
#include <regex>
#include <string>
#include <string_view>

constexpr std::string_view cmake_root_boilerplate (
R"(cmake_minimum_required(VERSION {})

project({} CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER g++)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_subdirectory(src)
)");

constexpr std::string_view cmake_src_boilerplate (
R"(add_executable({0})

target_link_libraries(
    {0}
    PUBLIC
)

target_sources(
    {0}
    PRIVATE
    main.cpp
))");



command_status get_cmake_version(std::string &cmake_version) {
    std::string version_output = execute_command(std::string("cmake --version"));

    std::regex pattern("[0-9]+\\.[0-9]+\\.[0-9]+");

    return get_first_of(version_output, pattern, cmake_version);
}

command_status get_working_directory_name(std::string &working_directory) {
    std::string pwd_output = execute_command(std::string("pwd"));

    std::regex pattern("[^/]*$");

    auto status = get_first_of(pwd_output, pattern, working_directory);
    if (status.is_error()) {
        return status;
    }

    // Strip the final newline
    working_directory.erase(working_directory.size() - 1);

    return COMMAND_SUCCESS;
}

command_status create_root_cmakelists() {
    std::string cmake_version;
    auto status = get_cmake_version(cmake_version);
    if (status.is_error()) {
        return status;
    } 

    std::string working_directory;
    status = get_working_directory_name(working_directory);
    if (status.is_error()) {
        return status;
    }

    std::string cmake_text = std::format(cmake_root_boilerplate, cmake_version, working_directory);

    status = create_file("CMakeLists.txt", cmake_text);
    if (status.is_error()) {
        return status;
    }

    return COMMAND_SUCCESS;
}

command_status create_src_cmakelists() {
    std::string working_directory;
    auto status = get_working_directory_name(working_directory);
    if (status.is_error()) {
        return status;
    }

    std::string cmake_text = std::format(cmake_src_boilerplate, working_directory);

    status = create_file("./src/CMakeLists.txt", cmake_text);
    if (status.is_error()) {
        return status;
    }

    return COMMAND_SUCCESS;
}

command_status create_build_dir() {
    if (!std::filesystem::create_directory("build")) {
        return COMMAND_FAIL;
    }
    return COMMAND_SUCCESS;
}

command_status create_src_dir() {
    if (!std::filesystem::create_directory("src")) {
        return COMMAND_CANNOT_CREATE_FILE;
    }

    auto status = create_src_cmakelists();
    if (status.is_error()) {
        return status;
    }

    status = create_file("./src/main.cpp");
    if (status.is_error()) {
        return status;
    }

    return COMMAND_SUCCESS;
}

command_status bootstrap_cmake() {
    auto status = create_root_cmakelists();
    if (status.is_error()) {
        return status;
    }

    status = create_build_dir();
    if (status.is_error()) {
        return status;
    }

    status = create_src_dir();
    if (status.is_error()) {
        return status;
    }

    return COMMAND_SUCCESS;
}
