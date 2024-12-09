#include "Sprite.h"

Sprite::Sprite(Texture* texture, std::string name) : Node2D(name){
	this->texture = texture;
}

void Sprite::ready() { 
	__super::ready();
}

void Sprite::update(float delta) {
	__super::update(delta);
	if (texture != nullptr) {
		this->texture->draw(position.x, position.y, scale.x, scale.y);
	}
	
}
