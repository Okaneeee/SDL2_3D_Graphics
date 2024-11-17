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
 * @param original Point to rotate
 * @param x Rotation in the X axis
 * @param y Rotation in the Y axis
 * @param z Rotation in the Z axis
 */
Vector3 rotate(const Vector3& original, float x = 1, float y = 1, float z = 1)
{
    // Create a copy of the original point to apply rotation
    Vector3 rotated = original;

    float rad;

    // Rotate around the X axis
    rad = x;
    float tempY = rotated.y * cos(rad) - rotated.z * sin(rad);
    float tempZ = rotated.y * sin(rad) + rotated.z * cos(rad);
    rotated.y = tempY;
    rotated.z = tempZ;

    // Rotate around the Y axis
    rad = y;
    float tempX = rotated.x * cos(rad) + rotated.z * sin(rad);
    tempZ = -rotated.x * sin(rad) + rotated.z * cos(rad);
    rotated.x = tempX;
    rotated.z = tempZ;

    // Rotate around the Z axis
    rad = z;
    tempX = rotated.x * cos(rad) - rotated.y * sin(rad);
    tempY = rotated.x * sin(rad) + rotated.y * cos(rad);
    rotated.x = tempX;
    rotated.y = tempY;

    return rotated;
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
    // Calculate the distance between the two points
    float dx = x2 - x1;
    float dy = y2 - y1;

    // Calculate the number of steps to take
    int steps = std::max(std::abs(dx), std::abs(dy));

    // Calculate the increment in each axis
    float x_inc = dx / steps;
    float y_inc = dy / steps;

    // Draw the line
    for(int i = 0; i < steps; i++) {
        screen.pixel(x1 + i * x_inc, y1 + i * y_inc);
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
        for (auto& point : points)
        {
            // Subtract the centre from the point
            Vector3 translatedPoint = { point.x - centre.x, point.y - centre.y, point.z - centre.z };

            // Rotate the translated point
            Vector3 rotatedPoint = rotate(translatedPoint, 0.2, 0.1, 0.4);

            // Add back the centre to the rotated point
            point.x = rotatedPoint.x + centre.x;
            point.y = rotatedPoint.y + centre.y;
            point.z = rotatedPoint.z + centre.z;

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
