#include "Texture.h"



Texture::Texture() {
	SDL_Renderer* renderer = SDL_GetRenderer(SDL_GetWindowFromID(1));
	this->renderer = renderer;
}

Texture::Texture(SDL_Surface* surface) {
	SDL_Renderer* renderer = SDL_GetRenderer(SDL_GetWindowFromID(1));
	this->renderer = renderer;
	setTexture(surface);
}

Texture::Texture(std::string texturePath) {
	SDL_Renderer* renderer = SDL_GetRenderer(SDL_GetWindowFromID(1));
	this->renderer = renderer;
	setTexture(texturePath);
}

Texture::~Texture() {
	SDL_DestroyTexture(this->texture); //have to destroy the SDL_Texture otherwise it will stay allocated in memory
										   //even if we delete this Texture class
}

void Texture::draw(Vector2D position, Vector2D scale , Vector2D bounds , Vector2D start, Vector2D size, SDL_RendererFlip flip) {
	draw(position.x, position.y, scale.x, scale.y, bounds.x, bounds.y, start.x, start.y, size.x, size.y, flip);
}

void Texture::draw(float posX, float posY, float scaleX, float scaleY, int width, int height, int startX, int startY, int sizeX, int sizeY, SDL_RendererFlip flip) {
	SDL_FRect dstRect;

	dstRect.x = posX;
	dstRect.y = posY;

	//if width is less than 0, use the retrieved width values from SDL_QueryTexture. otherwise use the passed in width values
	dstRect.w = (width <= 0) ? dimensions.x * scaleX : width * scaleX;
	//if height is less than 0, use the retrieved height values from SDL_QueryTexture. otherwise use the passed in height values
	dstRect.h = (height <= 0) ? dimensions.y * scaleY : height * scaleY;

	SDL_Rect srcRect;
	srcRect.x = (startX < 0) ? 0 : startX;
	srcRect.y = (startY < 0) ? 0 : startY;
	srcRect.w = (sizeX < 0) ? dstRect.w / scaleX : sizeX;
	srcRect.h = (sizeY < 0) ? dstRect.h / scaleY : sizeY;

	

	SDL_RenderCopyExF(this->renderer, texture, &srcRect, &dstRect, 0, NULL, flip);
}

//used for creating text on screen using fonts
void Texture::setTexture(SDL_Surface* surface) {
	if(texture != nullptr) {
		SDL_DestroyTexture(texture);
	}

	texture = SDL_CreateTextureFromSurface(this->renderer, surface);

	if (texture == NULL) {
		std::cout << "SURFACE IS NOT VALID " << surface << "\n";
	}
	else {
		generateTextureDimensions();
	}

}

//used to get images and set them as textures to render on screen
void Texture::setTexture(std::string newTexturePath) {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}

	texture = IMG_LoadTexture(this->renderer, newTexturePath.c_str());
	
	if (texture == NULL) {
		std::cout << "TEXTURE NOT FOUND at " << newTexturePath << "\n";
	}
	else {
		this->texturePath = newTexturePath;
		generateTextureDimensions();
	}
}

void Texture::generateTextureDimensions() {
	int w; 
	int h; 

	SDL_QueryTexture(this->texture, NULL, NULL, &w, &h); //gets the width and height of the texture
	dimensions = Vector2D(w, h);
}

Vector2D Texture::getDimensions() {
	return this->dimensions;
}