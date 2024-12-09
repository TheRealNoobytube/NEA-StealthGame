#pragma once
#include "SDL.h"

struct Color {
    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = SDL_ALPHA_OPAQUE) : r(r), g(g), b(b), a(a) {} //constructer shorthand

    Uint8 r = 0;
    Uint8 g = 0;
    Uint8 b = 0;
    Uint8 a = SDL_ALPHA_OPAQUE;
};