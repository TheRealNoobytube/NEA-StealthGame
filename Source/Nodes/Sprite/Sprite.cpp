#include "Sprite.h"
#include <iostream>

Sprite::Sprite(Texture* texture) {
	setName("Sprite");
	this->texture = texture;
}

void Sprite::ready() { 
	__super::ready();

	//this->texture = new Texture(getSceneTree()->getRenderer(), getSceneTree()->getBasePath() + "../Assets/testsprite.png");

}

void Sprite::update(float delta) {
	__super::update(delta);
	this->texture->draw(posX, posY, scaleX, scaleY);
}


//"C:\\Users\\nooby\\Documents\\Programs\\NEA Stealth Game\\Assets\\testsprite.png"