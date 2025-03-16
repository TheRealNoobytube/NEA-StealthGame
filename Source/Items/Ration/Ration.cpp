#include "Ration.h"


Ration::Ration(std::string name) : Item(name) {
	sprite->frame = 0;
	
}

void Ration::ready() {
	__super::ready();

	consumable = true;
	stackable = true;

	useSpeed = 0.1;
}

void Ration::onUse() {
	owner->health->heal(healingAmount);
}