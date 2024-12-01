#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Timer.h"
#include "../Nodes/Node.h"
#include "../Nodes/Sprite/Sprite.h"
#include "Data Structures/List.h"

class Application {
private:
    SDL_Renderer* renderer;

    struct Color {
        Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = SDL_ALPHA_OPAQUE) : r(r), g(g), b(b), a(a){} //constructer shorthand

        Uint8 r = 0;
        Uint8 g = 0;
        Uint8 b = 0;
        Uint8 a = SDL_ALPHA_OPAQUE;
    };

    std::string appName = "Stealth Game";
    int screenWidth = 1280;
    int screenHeight = 720;
    Color bgColor = Color(96, 96, 96);

public:
	bool applicationExited();

    void launch();
    virtual void applicationReady();
    virtual void applicationUpdate(float delta);
    virtual void applicationPhysicsUpdate(float delta);

    SDL_Renderer* Application::getRenderer();
};

