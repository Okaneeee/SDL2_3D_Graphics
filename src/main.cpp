#define SDL_MAIN_HANDLED // Avoid WinMain error
#include <screen.hpp>

int main(int argc, char* argv[]) {
    Screen screen;

    // Add 100 random pixels
    for(int i = 0; i < 100; i++) {
        screen.pixel(rand()%SCREEN_WIDTH, rand()%SCREEN_HEIGHT);
    }

    // Main loop
    while(true)
    {
        screen.show(); // Showing the screen
        screen.input(); // Check if the user wants to close the window
    }

}
