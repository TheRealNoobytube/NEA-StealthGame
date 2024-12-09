#include "Texture.h"



Texture::Texture(SDL_Renderer* renderer, SDL_Surface* surface) {
	this->renderer = renderer;
	setTexture(surface);
}

Texture::Texture(SDL_Renderer* renderer, std::string texturePath) {
	this->renderer = renderer;
	setTexture(texturePath);
}

Texture::~Texture() {
	if (this->texture != nullptr) {
		SDL_DestroyTexture(this->texture); //have to destroy the SDL_Texture otherwise it will stay allocated in memory
										   //even if we delete this Texture class
	}
}


void Texture::draw(float posX, float posY, float scaleX, float scaleY) {
	SDL_FRect dstRect;
	int w; //create seperate w and h variables because SDL_FRect w and h are floats
	int h; //so we can't pass them as referencces into the SDL_QueryTexture procedure

	SDL_QueryTexture(this->texture, NULL, NULL, &w, &h); //gets the width and height of the texture
	                                                     //needed because otherwise texture will be drawn as big as the window
	dstRect.x = posX;
	dstRect.y = posY;
	dstRect.w = w * scaleX;
	dstRect.h = h * scaleY;

	
	SDL_RenderCopyF(this->renderer, texture, NULL, &dstRect);
}

//used for creating text on screen using fonts
void Texture::setTexture(SDL_Surface* surface) {
	texture = SDL_CreateTextureFromSurface(this->renderer, surface);

	if (texture == NULL) {
		std::cout << "SURFACE IS NOT VALID " << surface << "\n";
	}

}

//used to get images and set them as textures to render on screen
void Texture::setTexture(std::string newTexturePath) {
	texture = IMG_LoadTexture(this->renderer, newTexturePath.c_str());
	
	if (texture == NULL) {
		std::cout << "TEXTURE NOT FOUND at " << newTexturePath << "\n";
	}
	else {
		this->texturePath = newTexturePath;
	}
}