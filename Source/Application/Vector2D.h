#pragma once

struct Vector2D {
    Vector2D(float x = 0, float y = 0) : x(x), y(y) {} // constructer shorthand

    float x = 0;
    float y = 0;

    // shortens a vectors magnitude to 1, useful when all you need is the direction the vector is pointing at
    Vector2D normalized() { 
        float magnitude = getMagnitude();
        // when the magnitude is 0, we just return a direction vector of 0
        return (magnitude != 0) ? Vector2D(x / magnitude, y / magnitude) : Vector2D(0,0);
    }

    Vector2D fixDirection() {
        Vector2D newDirection;
        newDirection.x = round(x);
        newDirection.y = round(y);

        return newDirection;
    }

    float getMagnitude() {
        return sqrt((x * x) + (y * y));
    }


    Vector2D directionTo(Vector2D position) {
        return Vector2D(position.x - x, position.y - y).normalized();
        //return Vector2D(cos(position.x - x), sin(position.y - y));
        
    }

    float distanceTo(Vector2D position) {
        float xDiff = x - position.x;
        float yDiff = y - position.y;
        return sqrt((xDiff * xDiff) + (yDiff * yDiff));
    }

    bool operator==(const Vector2D &vec) {
        return x == vec.x && y == vec.y;
    }

    bool operator!=(const Vector2D& vec) {
        return x != vec.x || y != vec.y;
    }
};