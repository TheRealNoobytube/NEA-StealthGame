#pragma once

#include "Source/Nodes/AnimatedSprite/AnimatedSprite.h"
#include "Source/Collision/Raycast/Raycast.h"
#include "Source/Collision/CollisionBody.h"
#include "Source/Collision/CollisionShapes/CollisionRect.h"
#include "Source/Components/Movement/MovementComponent.h"
#include "Source/Components/Health/HealthComponent.h"
#include "Source/Components/Items/ItemsComponent.h"

class Entity : public CollisionBody {
private:
	void damaged(float damage);
	void death(float damage);


public:
	Entity(std::string name = "Entity");

	HealthComponent* health = new HealthComponent(this);
	MovementComponent* movement = new MovementComponent(this);

	ItemsComponent* itemInventory = new ItemsComponent(false, this);
	ItemsComponent* weaponInventory = new ItemsComponent(true, this);

	float speed;

	virtual void onDamaged(float damage);
	virtual void onDeath(float damage);

	virtual void onItemPickup(Item* item);
	virtual void onItemSwitched(Item* item);
	virtual void onItemUsed(Item* item);

	virtual void onWeaponPickup(Item* weapon);
	virtual void onWeaponSwitched(Item* weapon);
	virtual void onWeaponUsed(Item* weapon);
};

