#pragma once

#include <cstdio>

#define COMMAND_SUCCESS command_status::_COMMAND_SUCCESS()
#define COMMAND_FAIL command_status::_COMMAND_FAIL()
#define COMMAND_NO_MATCH command_status::_COMMAND_NO_MATCH()
#define COMMAND_CANNOT_CREATE_FILE command_status::_COMMAND_CANNOT_CREATE_FILE()

class command_status {
public:
    static command_status _COMMAND_SUCCESS() {
        return command_status(_status::_COMMAND_SUCCESS);
    }

    static command_status _COMMAND_FAIL() {
        return command_status(_status::_COMMAND_GENERAL_FAIL);
    }

    static command_status _COMMAND_NO_MATCH() {
        return command_status(_status::_COMMAND_NO_MATCH);
    }

    static command_status _COMMAND_CANNOT_CREATE_FILE() {
        return command_status(_status::_COMMAND_CANNOT_CREATE_FILE);
    }

    inline bool is_error() {
        return m_status == _status::_COMMAND_SUCCESS ? false : true;
    }

    inline int get_code() {
        return static_cast<int>(m_status);
    }

    void print() {
        switch (m_status) {
        case _status::_COMMAND_SUCCESS:
            printf("Command succeded.\n");
            break;
        case _status::_COMMAND_GENERAL_FAIL:
            printf("A nondescript error occurred.\n");
            break;
        case _status::_COMMAND_NO_MATCH:
            printf("Unable to find match.\n");
            break;
        case _status::_COMMAND_CANNOT_CREATE_FILE:
            printf("Failed to create file or directory.\n");
            break;
        default:
            printf("No print found for this status.\n");
            break;
        }

        return;
    }

private:
    enum class _status {
        _COMMAND_SUCCESS = 0,
        _COMMAND_GENERAL_FAIL,
        _COMMAND_NO_MATCH,
        _COMMAND_CANNOT_CREATE_FILE
    };

    _status m_status;

    // Constructor made private to hide status
    command_status(_status status) : m_status(status) {}
};
