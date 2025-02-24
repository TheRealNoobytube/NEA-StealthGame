#include "Ration.h"


Ration::Ration(std::string name) : Item(name) {

}

void Ration::ready() {
	__super::ready();

	sprite.frame = 0;

	consumable = true;
	stackable = true;
}