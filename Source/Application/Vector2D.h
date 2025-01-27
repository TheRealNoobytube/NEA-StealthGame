#pragma once

struct Vector2D {
    Vector2D(float x = 0, float y = 0) : x(x), y(y) {} // constructer shorthand

    float x = 0;
    float y = 0;

    // shortens a vectors magnitude to 1, useful when all you need is the direction the vector is pointing at
    Vector2D normalized() { 
        float magnitude = sqrtf((x * x) + (y * y));
        // when the magnitude is 0, we just return a direction vector of 0
        return (magnitude != 0) ? Vector2D(x / magnitude, y / magnitude) : Vector2D(0,0);
    }

    bool operator==(const Vector2D &vec) {
        return x == vec.x && y == vec.y;
    }

    bool operator!=(const Vector2D& vec) {
        return x != vec.x || y != vec.y;
    }
};