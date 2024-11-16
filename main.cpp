#define SDL_MAIN_HANDLED // Avoid WinMain error
#include <SDL.h>

int main(int argc, char* argv[]) {
    // SDL initialization
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Erreur d'initialisation de SDL : %s", SDL_GetError());
        return -1;
    }

    // SDL Window
    SDL_Window* window = SDL_CreateWindow("Test",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("Error when creating the window : %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Wait 3 seconds
    SDL_Delay(3000);

    // Clean and quit
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
