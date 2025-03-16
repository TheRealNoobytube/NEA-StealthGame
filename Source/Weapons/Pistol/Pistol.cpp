#include "Pistol.h"

Pistol::Pistol(std::string name) : Item(name){
	sprite->frame = sprite->getHFrames();
}

void Pistol::ready() {
	__super::ready();
	isWeapon = true;
	consumable = false;
	stackable = false;

	useSpeed = 0.3;
}

void Pistol::update(float delta) {
	__super::update(delta);

}

void Pistol::onUse() {
	if (owner != nullptr) {

		PistolShot* projectile = new PistolShot();
		projectile->position = owner->getGlobalPosition();
		projectile->movement->direction = owner->movement->direction;
		projectile->position.x += 5 * projectile->movement->direction.x;
		projectile->position.y += -10;

		projectile->owner = owner;

		Level* level = reinterpret_cast<Level*>(getSceneTree()->getCurrentScene());
		level->projectileLayer->addChild(projectile);

		if (enemyItem) {
			projectile->mask = WORLD | PLAYER;
		}
	}

}