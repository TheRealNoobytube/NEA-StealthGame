#pragma once
#include <iostream>
#include "SDL.h"

class Application {
private:
    SDL_Renderer* renderer;

    struct color {
        int r = 0;
        int g = 0;
        int b = 0;
    };

    struct vector2 {
        float x;
        float y;
    };

    struct square {
        vector2 pos;
        vector2 dim;
        color col;
    };

    std::string appName = "Stealth Game";
    int screenWidth = 640;
    int screenHeight = 480;
    color bgColor = color(96, 96, 96);

public:
	bool ApplicationExited();

    void DrawPixel(vector2 p1);
	void DrawLine(vector2 p1, vector2 p2);
    void Launch();
    virtual void ApplicationReady();
    virtual void ApplicationUpdate();
};

