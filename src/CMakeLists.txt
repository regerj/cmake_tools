add_executable(cmt)

target_include_directories(
    cmt
    PUBLIC
    .
)

target_sources(
    cmt
    PRIVATE
    main.cpp
    bootstrap_command.cpp
    command_execute.cpp
    create_files_command.cpp
    utils.cpp
)
