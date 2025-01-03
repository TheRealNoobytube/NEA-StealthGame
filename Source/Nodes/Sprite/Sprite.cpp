#include "Sprite.h"

Sprite::Sprite(std::string filepath, std::string name) : Node2D(name){
	setTexture(filepath);
}

Sprite::Sprite(Texture* texture, std::string name) : Node2D(name){
	setTexture(texture);
}

Sprite::~Sprite() {
	delete this->texture;
}

void Sprite::ready() { 
	__super::ready();
}

void Sprite::update(float delta) {
	__super::update(delta);
	if (texture != nullptr) {
		// SDL_FLIP_VERTICALLY const has a value of 2, so we multiply flipV by 2 to make sure that, if flipV is true, it flips vertically
		SDL_RendererFlip flip = static_cast<SDL_RendererFlip>(flipH | (flipV * 2));
		Vector2D globalPosition = getGlobalPosition();
		Vector2D dimensions = this->texture->getDimensions();
		float textureWidth = dimensions.x / hFrames;
		float textureHeight = dimensions.y / vFrames;

		int framePosX = frame % hFrames;
		int framePosY = floor(frame / hFrames);

		this->texture->draw(globalPosition,
			scale,
			Vector2D(textureWidth, textureHeight),
			Vector2D(textureWidth * framePosX, textureHeight * framePosY),
			Vector2D(textureWidth, textureHeight),
			flip);
	}
	
}

void Sprite::setTexture(Texture* texture) {
	this->texture = texture;
}

void Sprite::setTexture(std::string filepath) {
	if (!filepath.empty()) {
		Texture* texture = new Texture(filepath);
		setTexture(texture);
	}
}


//void Sprite::setFrame(int frame) {
//	if (frame < 0) {
//		this->frame = 0;
//	}
//	else if (frame > hFrames * vFrames) {
//		this->frame = (hFrames * vFrames) - 1;
//	}
//	else {
//		this->frame = frame;
//	}
//}
//
//int Sprite::getFrame() {
//	return this->frame;
//}


void Sprite::setVFrames(int vFrames) {
	if (vFrames < 1) {
		this->vFrames = 1;
	}
	else {
		this->vFrames = vFrames;
	}
}

void Sprite::setHFrames(int hFrames) {
	if (hFrames < 1) {
		this->hFrames = 1;
	}
	else {
		this->hFrames = hFrames;
	}
}

int Sprite::getVFrames() {
	return this->vFrames;
}

int Sprite::getHFrames() {
	return this->hFrames;
}