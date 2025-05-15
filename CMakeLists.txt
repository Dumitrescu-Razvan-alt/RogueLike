cmake_minimum_required(VERSION 3.16)
project(RoguelikeGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use pkg-config to find SDL2 and SDL2_image
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    include
    include/Entities
    include/GameStates
    include/Map
    include/Observer
    include/UI
)

link_directories(
    ${SDL2_LIBRARY_DIRS}
    ${SDL2_IMAGE_LIBRARY_DIRS}
)

# Gather all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create executable
add_executable(Roguelike ${SOURCES})

# Link SDL2 and SDL2_image
target_link_libraries(Roguelike ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
