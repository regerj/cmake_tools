#include "bootstrap_command.h"
#include "create_files_command.h"

#include <cstdio>
#include <string>

int main (int argc, char *argv[]) {
    if (argc == 1) {
        printf("Incorrect number of arguments!\n");
    }

    std::string command_name = std::string(argv[1]);

    if (command_name == std::string("bootstrap")) {
        auto status = bootstrap_cmake();
        if (status.is_error()) {
            status.print();
            return status.get_code();
        }
    } else if (command_name == std::string("create_files")) {
        std::string file_name = std::string(argv[2]);

        auto status = create_files(file_name);
        if (status.is_error()) {
            status.print();
            return status.get_code();
        }


    }

    return 0;
}
