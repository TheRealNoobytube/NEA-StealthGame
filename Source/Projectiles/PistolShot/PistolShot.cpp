#include "PistolShot.h"


PistolShot::PistolShot(std::string name) : Projectile(name){

}

void PistolShot::ready() {
	__super::ready();
	speed = 3.5;
}
