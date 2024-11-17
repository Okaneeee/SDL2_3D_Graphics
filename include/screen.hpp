#include <SDL.h>
#include <vector>

// Constants
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class Screen
{
private:
    // SDL basic elements
    SDL_Event e;
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<SDL_FPoint> points;

public:
    // Constructor
    Screen()
    {
        SDL_Init(SDL_INIT_VIDEO);
        // Creating the window and the renderer
        SDL_CreateWindowAndRenderer(
            SCREEN_WIDTH*2, // Multiplying the resolution by the scale
            SCREEN_HEIGHT*2, // Multiplying the resolution by the scale
            0,
            &window,
            &renderer
        );
        SDL_RenderSetScale(renderer, 2, 2);
    }

    /**
     * Add a pixel to the screen
     * @param x X coordinate
     * @param y Y coordinate
     */
    void pixel(float x, float y)
    {
        // Creates a new point struct and adds it to the vector
        points.emplace_back(x, y); // use push_back if emplace_back doesn't work
    }

    /**
     * Show the screen
     */
    void show()
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Draw color: black
        SDL_RenderClear(renderer); // Clear the screen

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Draw color: white
        // Draw all the points
        for(auto& point : points)
        {
            SDL_RenderDrawPointF(renderer, point.x, point.y);
        }

        SDL_RenderPresent(renderer); // Show the screen
    }

    /**
     * Handle the inputs
     */
    void input()
    {
        while(SDL_PollEvent(&e))
        {
            // Check if the user wants to close the window
            if(e.type == SDL_QUIT)
            {
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                exit(0);
            }
        }
    }
};