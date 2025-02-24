#include "Pistol.h"

Pistol::Pistol(std::string name) : Item(name){

}

void Pistol::ready() {
	__super::ready();
	sprite.frame = sprite.getHFrames();
	isWeapon = true;
	consumable = false;
	stackable = false;

}

void Pistol::update(float delta) {
	__super::update(delta);
}