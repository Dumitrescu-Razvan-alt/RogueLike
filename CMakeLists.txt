cmake_minimum_required(VERSION 3.10)
project(Game)

set(CMAKE_CXX_STANDARD 17)

add_executable(game src/main.cpp)
target_include_directories(game PRIVATE include)
