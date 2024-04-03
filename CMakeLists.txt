cmake_minimum_required(VERSION 3.27.1)

project(CMakeTools CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER g++)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# include(FetchContent)
# FetchContent_Declare(
#   taywee_args
#   GIT_REPOSITORY git@github.com:Taywee/args.git
#   GIT_TAG        6.4.6
# )

# FetchContent_MakeAvailable(taywee_args)

add_subdirectory(src)
