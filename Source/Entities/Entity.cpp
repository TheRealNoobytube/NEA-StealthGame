#include "Entity.h"



Entity::Entity(std::string name) : CollisionBody(name) {
	layer = ENTITIES;
	mask = WORLD | ENTITIES;

	addChild(health);
	health->damaged.connect([this](float damage) { damaged(damage); });
	health->death.connect([this](float damage) { death(damage); });
	health->setMaxHealth(3);

	addChild(movement);

	addChild(itemInventory);
	itemInventory->pickup.connect([this](Item* item) { onItemPickup(item); });
	itemInventory->item_switched.connect([this](Item* item) { onItemSwitched(item); });
	itemInventory->used.connect([this](Item* item) { onItemUsed(item); });

	addChild(weaponInventory);
	weaponInventory->pickup.connect([this](Item* weapon) { onWeaponPickup(weapon); });
	weaponInventory->item_switched.connect([this](Item* weapon) { onWeaponSwitched(weapon); });
	weaponInventory->used.connect([this](Item* weapon) { onWeaponUsed(weapon); });
}

void Entity::damaged(float damage) {

	onDamaged(damage);
}

void  Entity::onDamaged(float damage) {}


void Entity::death(float damage) {
	onDeath(damage);
}

void  Entity::onDeath(float damage) {}

void Entity::onItemPickup(Item* item) {}

void Entity::onItemSwitched(Item* item) {}

void Entity::onItemUsed(Item* item) {}


void Entity::onWeaponPickup(Item* weapon) {}

void Entity::onWeaponSwitched(Item* weapon) {}

void Entity::onWeaponUsed(Item* weapon) {}