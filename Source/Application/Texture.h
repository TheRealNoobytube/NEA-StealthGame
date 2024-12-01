#pragma once
#include <string>
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

class Texture {
private:
	std::string texturePath;
	SDL_Renderer* renderer;
	SDL_Texture* texture;

public:
	Texture(SDL_Renderer* renderer, std::string texturePath);
	void draw(float posX, float posY, float scaleX = 1, float scaleY = 1);

	void setTexture(std::string newTexturePath);
};