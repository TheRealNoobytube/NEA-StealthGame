#pragma once
#include <string>
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Vector2D.h"

class Texture {
private:
	std::string texturePath;
	SDL_Renderer* renderer;
	SDL_Texture* texture = nullptr;

	Vector2D dimensions = Vector2D(0, 0);

	void generateTextureDimensions();

public:
	Texture();
	Texture(SDL_Surface* surface);
	Texture(std::string texturePath);
	~Texture();

	void draw(Vector2D position, Vector2D scale = Vector2D(1, 1), Vector2D bounds = Vector2D(0, 0), Vector2D start = Vector2D(-1, -1), Vector2D size = Vector2D(-1, -1), SDL_RendererFlip flip = SDL_FLIP_NONE);

	void draw(float posX, float posY, float scaleX = 1, float scaleY = 1, int width = 0, int height = 0, int startX = -1, int startY = -1, int sizeX = -1, int sizeY = -1, SDL_RendererFlip flip = SDL_FLIP_NONE);


	void setTexture(std::string newTexturePath);
	void setTexture(SDL_Surface* surface);

	SDL_Texture* getTexture();

	Vector2D getDimensions();
};