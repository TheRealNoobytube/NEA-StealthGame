#include "Texture.h"



Texture::Texture(SDL_Renderer* renderer, std::string texturePath) {
	this->renderer = renderer;
	setTexture(texturePath);
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


void Texture::setTexture(std::string newTexturePath) {
	texture = IMG_LoadTexture(this->renderer, newTexturePath.c_str()); //convert to c string because SDL is written in C which doesn't have standard strings
	
	if (texture == NULL) {
		std::cout << "TEXTURE NOT FOUND at " << newTexturePath << "\n";
	}
	else {
		this->texturePath = texturePath;
	}
}