#include "Application.h"

bool Application::applicationExited() {
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
        return true;
    }
    return false;
}


void Application::launch() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow(
        appName.c_str(), //must pass in as C string because SDL2 is a C library and won't know what to do with a c++ string
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        screenWidth,
        screenHeight,
        SDL_WINDOW_RESIZABLE // allows the window to be resizable, but you already knew that
    );

    SDL_SetWindowMinimumSize(window, 640, 360);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    Timer updateTimer = Timer();
    updateTimer.start();

    const int FPS = 60;
    const float NANOSECONDSPERFRAME = 1000000000 / (float) FPS;
    float lastUpdate = updateTimer.getTime_Nano();
    float lastIteration = updateTimer.getTime_Nano();
    float lag = 0.0;

    //When loop starts, we have to have a whole frame of time before the first update call
    //So we call both update methods outside the loop to account for this
    applicationReady();
    applicationUpdate(NANOSECONDSPERFRAME);
    applicationPhysicsUpdate(NANOSECONDSPERFRAME);

    //Update loop

    while (!applicationExited()) {
        float currentTime = updateTimer.getTime_Nano();
        float elapsed = currentTime - lastUpdate;
        lag += currentTime - lastIteration;

        lastIteration = currentTime;


        if (elapsed >= NANOSECONDSPERFRAME) {
            SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
            SDL_RenderClear(renderer); //window gets cleared before rendering new screen

            //physicsUpdate is fixed, and therefore any lag between physicsUpdates must be accounted for in order to get accurate phsyics
            while (lag >= NANOSECONDSPERFRAME) { 
                applicationPhysicsUpdate(NANOSECONDSPERFRAME); //deltaTime is nanoseconds per frame because time between physicsUpdates is fixed
                lag -= NANOSECONDSPERFRAME;
            }
            //we wait to do all the unaccounted physicsUpdates before we move on to rendering, as otherwise we'll be constantly rendering
            //which could contribute to lag between physicsUpdate frames

            applicationUpdate(elapsed); //elapsed already calculates the time it took between updates, therefore passed in as deltaTime

            SDL_RenderPresent(renderer); //present final render

            lastUpdate = currentTime;
        }
        
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Application::applicationReady(){
}
void Application::applicationUpdate(float delta){
}
void Application::applicationPhysicsUpdate(float delta) {
}

SDL_Renderer* Application::getRenderer() {
    return this->renderer;
}