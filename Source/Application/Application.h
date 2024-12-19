#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Timer.h"
#include "Color.h"
#include "Vector2D.h"
#include "Data Structures/List.h"

#include "Source/Nodes/Node.h"
#include "Source/Nodes/Node2D/Node2D.h"
#include "Source/Nodes/Sprite/Sprite.h"

#include "Source/UI/Label/Label.h"
#include "Source/UI/Button/Button.h"


class Application {
private:
    SDL_Renderer* renderer;
    SDL_Window* window;

    const int FPS = 60;
    const float NANOSECONDSPERFRAME = 1000000000 / (float)FPS;

    std::string appName = "Stealth Game";
    std::string basePath = SDL_GetBasePath();
    int screenWidth = 1280;
    int screenHeight = 720;
    int viewportWidth = 320;
    int viewportHeight = 180;
    Vector2D renderScale = Vector2D(1, 1);

    Color bgColor = Color(96, 96, 96);

public:
	bool applicationExited(SDL_Event& event);
    void onApplicationExited();

    std::string getBasePath();

    void launch();
    virtual void applicationReady();
    virtual void applicationUpdate(float delta);
    virtual void applicationPhysicsUpdate(float delta);
    virtual void handleInput(SDL_Event& event);

    void stretchWindow();

    SDL_Renderer* getRenderer();
    SDL_Window* getWindow();

    Vector2D getViewportSize();
};

