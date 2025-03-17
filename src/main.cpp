#include <iostream>
#include <unistd.h> // For sleep

void clearScreen() {
    std::cout << "\033[2J\033[H"; // ANSI escape sequence to clear the screen
}

void render() {
    clearScreen();
    // Your game rendering logic goes here
    std::cout << "Game is running!" << std::endl;
    std::cout << "Game is running!" << std::endl;
    std::cout << "Game is running!" << std::endl;
    std::cout << "Game is running!" << std::endl;
    std::cout << "Game is running!" << std::endl;
}

int main() {
    while (true) {
        render();
        usleep(100000); // Sleep for 100ms (10 FPS)
    }
    return 0;
}
