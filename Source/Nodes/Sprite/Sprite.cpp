#include "Sprite.h"
#include <iostream>


Sprite::Sprite(std::string texturePath) {
	setName("Sprite");
	Texture texture = Texture(getSceneTree()->getRenderer(), texturePath);
	this->texture = texture;
}

Sprite::Sprite(Texture texture) {
	setName("Sprite");
	this->texture = texture;
}

Sprite::Sprite() {
	setName("Sprite");
}



void Sprite::ready() { 
	__super::ready();
	this->texture = Texture(getSceneTree()->getRenderer(), "C:\\Users\\nooby\\Documents\\Programs\\NEA Stealth Game\\Assets\\testsprite.png");

}

void Sprite::update(float delta) {
	__super::update(delta);
	this->texture.draw(posX, posY);

}


//"C:\\Users\\nooby\\Documents\\Programs\\NEA Stealth Game\\Assets\\testsprite.png"