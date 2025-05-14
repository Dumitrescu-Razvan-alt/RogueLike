cmake_minimum_required(VERSION 3.16)
project(RoguelikeGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find SDL2 (you can customize this for your OS/setup)
find_package(SDL2 REQUIRED)

# Include SDL2 headers
include_directories(${SDL2_INCLUDE_DIRS})

# Include souece file headers
include_directories(include)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(Roguelike ${SOURCES})

# Link SDL2 libraries
target_link_libraries(Roguelike ${SDL2_LIBRARIES})
