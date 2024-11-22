#pragma once
#include <iostream>
#include "SDL.h"
#include "Timer.h"

class Application {
private:
    SDL_Renderer* renderer;

    struct color {
        color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = SDL_ALPHA_OPAQUE) : r(r), g(g), b(b), a(a){} //constructer shorthand

        Uint8 r = 0;
        Uint8 g = 0;
        Uint8 b = 0;
        Uint8 a = SDL_ALPHA_OPAQUE;
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
    int screenWidth = 1280;
    int screenHeight = 720;
    color bgColor = color(96, 96, 96);

public:
	bool applicationExited();

    void drawPixel(vector2 p1);
	void drawLine(vector2 p1, vector2 p2);
    void launch();
    virtual void applicationReady();
    virtual void applicationUpdate(float delta);
    virtual void applicationPhysicsUpdate(float delta);
};

