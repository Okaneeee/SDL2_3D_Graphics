#define SDL_MAIN_HANDLED // Avoid WinMain error
#include <screen.hpp>

void line(Screen& screen, float x1, float y1, float x2, float y2) {
    // Bresenham's line algorithm
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;

    while(true) {
        screen.pixel(x1, y1);
        if(x1 == x2 && y1 == y2) break;
        int e2 = 2*err;
        if(e2 > -dy) { err -= dy; x1 += sx; }
        if(e2 < dx) { err += dx; y1 += sy; }
    }
}

int main(int argc, char* argv[]) {
    Screen screen;

    // Add 100 random pixels
    for(int i = 0; i < 100; i++) {
        screen.pixel(rand()%SCREEN_WIDTH, rand()%SCREEN_HEIGHT);
    }

    line(screen, 100, 100, 200, 100);
    line(screen, 200, 100, 200, 200);
    line(screen, 200, 200, 100, 200);
    line(screen, 100, 200, 100, 100);

    // Main loop
    while(true)
    {
        screen.show(); // Showing the screen
        screen.input(); // Check if the user wants to close the window
    }

}
