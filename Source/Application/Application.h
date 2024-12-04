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
    SDL_Window* window;

    struct Color {
        Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = SDL_ALPHA_OPAQUE) : r(r), g(g), b(b), a(a){} //constructer shorthand

        Uint8 r = 0;
        Uint8 g = 0;
        Uint8 b = 0;
        Uint8 a = SDL_ALPHA_OPAQUE;
    };

    std::string appName = "Stealth Game";
    std::string basePath = SDL_GetBasePath();
    int screenWidth = 1280;
    int screenHeight = 720;
    int viewportWidth = 640;
    int viewportHeight = 360;
    Color bgColor = Color(96, 96, 96);

public:
	bool applicationExited(SDL_Event& event);
    void onApplicationExited();

    std::string getBasePath();

    void launch();
    virtual void applicationReady();
    virtual void applicationUpdate(float delta);
    virtual void applicationPhysicsUpdate(float delta);
    virtual void handleEvent(SDL_Event& event);

    void stretchWindow();

    SDL_Renderer* getRenderer();
    SDL_Window* getWindow();
};

