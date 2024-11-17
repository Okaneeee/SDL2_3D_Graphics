#define SDL_MAIN_HANDLED // Avoid WinMain error
#include <cmath>
#include <numeric>
#include <screen.hpp>

struct Vector3
{
    float x, y, z;
};

struct connection
{
    int a, b;
};

/**
 * Rotate a point in 3D space
 * @param point Point to rotate
 * @param x Rotation in the X axis
 * @param y Rotation in the Y axis
 * @param z Rotation in the Z axis
 */
void rotate(Vector3& point, float x = 1 , float y = 1, float z = 1)
{
    float rad = 0;

    point.y = point.y * cos(rad) - point.z * sin(rad);
    point.z = point.y * sin(rad) + point.z * cos(rad);

    rad = y;
    point.x = point.x * cos(rad) - point.z * sin(rad);
    point.z = point.x * sin(rad) + point.z * cos(rad);

    rad = z;
    point.x = point.x * cos(rad) - point.y * sin(rad);
    point.y = point.x * sin(rad) + point.y * cos(rad);

}

/**
 * Draw a line between two points
 * @param screen Screen object
 * @param x1 X coordinate of the first point
 * @param y1 Y coordinate of the first point
 * @param x2 X coordinate of the second point
 * @param y2 Y coordinate of the second point
 */
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

    // Cube points
    std::vector<Vector3> points{
        {100, 100, 100},
        {200, 100, 100},
        {200, 200, 100},
        {100, 200, 100},

        {100, 100, 200},
        {200, 100, 200},
        {200, 200, 200},
        {100, 200, 200}
    };

    std::vector<connection> connections{
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 0},

        {4, 5},
        {5, 6},
        {6, 7},
        {7, 4},

        {0, 4},
        {1, 5},
        {2, 6},
        {3, 7}
    };

    Vector3 centre {0, 0, 0};
    // Calculate the centre of the cube (centroid)
    for(auto& p : points)
    {
        // Summing up all the vertices x, y and z
        centre.x += p.x;
        centre.y += p.y;
        centre.z += p.z;
    }

    // Divide by the number of vertices
    centre.x /= points.size();
    centre.y /= points.size();
    centre.z /= points.size();

    // Main loop
    while(true)
    {
        // Draw and rotate the cube
        for(auto& point : points)
        {
            // Subtract the centre from the point
            point.x -= centre.x;
            point.y -= centre.y;
            point.z -= centre.z;

            rotate(point, 0.02, 0.01, 0.04);

            // Add back the centre to the point
            point.x += centre.x;
            point.y += centre.y;
            point.z += centre.z;

            // Draw the point
            screen.pixel(point.x, point.y);
        }

        for(auto& conn : connections)
        {
            line(screen, points[conn.a].x,
                            points[conn.a].y,
                            points[conn.b].x,
                            points[conn.b].y);
        }

        screen.show(); // Showing the screen
        screen.clear(); // Clearing the screen to avoid drawing the same points again

        screen.input(); // Check if the user wants to close the window
        SDL_Delay(30); // Delay
    }

    return 0;
}
