#define SDL_MAIN_HANDLED
#include "screen.h"
#include <cmath>


struct vec3
{
    float x, y, z;
};

struct connection
{
    int a, b;    
};

void rotate(vec3& point, float x = 1, float y = 1, float z = 1)
{
    float rad = 0;
    vec3 tmp = point;
    rad = x;
    point.y = std::cos(rad) * tmp.y - std::sin(rad) * tmp.z;
    point.z = std::sin(rad) * tmp.y + std::cos(rad) * tmp.z;
    tmp = point;

    rad = y;
    point.x = std::cos(rad) * tmp.x - std::sin(rad) * tmp.z;
    point.z = std::sin(rad) * tmp.x + std::cos(rad) * tmp.z;
    tmp = point;

    rad = z;
    point.x = std::cos(rad) * tmp.x - std::sin(rad) * tmp.y;
    point.y = std::sin(rad) * tmp.x + std::cos(rad) * tmp.y;
    tmp = point;
}

void line(Screen& screen, float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    float length = std::sqrt(dx * dx + dy * dy);
    float angle = std::atan2(dy, dx);

    for(float i = 0; i < length; i++)
    {
        screen.pixel(x1 + std::cos(angle) * i, y1 + std::sin(angle) * i);
    }
}

int main()
{
    Screen screen;
    //Cube
    /*
    std::vector<vec3> points { {-50, -50, -50}, {50, -50, -50}, {50, 50, -50}, {-50, 50, -50},
                               {-50, -50, 50}, {50, -50, 50}, {50, 50, 50}, {-50, 50, 50} };

    std::vector<connection> connections { {0, 4}, {1, 5}, {2, 6}, {3, 7},
                                          {0, 1}, {1, 2}, {2, 3}, {3, 0},
                                          {4, 5}, {5, 6}, {6, 7}, {7, 4} };
    */
    //Pyramid   (WIP)
    /*
    std::vector<vec3> points { {-50, -50, -50}, {50, -50, -50}, {50, 50, -50}, {-50, 50, -50}, {0, 0, 50} };

    std::vector<connection> connections { {0, 4}, {1, 4}, {2, 4}, {3, 4},
                                          {0, 1}, {1, 2}, {2, 3}, {3, 0} };
    */
    //Triangle Pyramid
    
    std::vector<vec3> points { {50, 50, 50}, {50, -50, -50}, {-50, 50, -50}, {-50, -50, 50} };

    std::vector<connection> connections { {0, 3}, {1, 3}, {2, 3},
                                          {0, 1}, {1, 2}, {2, 0} };
    
    //Calculate center point
    vec3 c{0, 0, 0};
    for(auto& p : points)
    {
        c.x += p.x;
        c.y += p.y;
        c.z += p.z;
    }
    c.x /= points.size();
    c.y /= points.size();
    c.z /= points.size();

    const float screenCenterX = 320;
    const float screenCenterY = 240;

    while(true)
    {
        for(auto& p : points)
        {
            p.x -= c.x;
            p.y -= c.y;
            p.z -= c.z;
            rotate(p, 0.02, 0.02, 0.02);
            p.x += c.x;
            p.y += c.y;
            p.z += c.z;
        }

        for(auto& p : points)
        {
            screen.pixel(p.x + screenCenterX, p.y + screenCenterY);
        }

        for(auto& conn : connections)
        {
            line(screen, points[conn.a].x + screenCenterX, points[conn.a].y + screenCenterY, points[conn.b].x + screenCenterX, points[conn.b].y + screenCenterY);
        }
        screen.show();
        screen.clear();
        screen.input();
        SDL_Delay(30);   
    }
    return 0;
}
