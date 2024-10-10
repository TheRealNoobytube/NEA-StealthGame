#include "Application.h"

bool Application::ApplicationExited() {
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
        return true;
    }
    return false;
}

void Application::DrawPixel(vector2 point) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawPointF(renderer, point.x, point.y);
}

void Application::DrawLine(vector2 point1, vector2 point2) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLineF(renderer, point1.x, point1.y, point2.x, point2.y);
}


void Application::Launch() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        appName.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        screenWidth,
        screenHeight,
        0
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    while (!ApplicationExited()) {
        SDL_RenderClear(renderer);

        ApplicationUpdate();
        SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, SDL_ALPHA_OPAQUE);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Application::ApplicationReady(){

}
void Application::ApplicationUpdate(){

}