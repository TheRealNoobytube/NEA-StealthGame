#pragma once
#include "Source/Nodes/Node2D/Node2D.h"
#include "Source/Collision/CollisionBody.h"
#include "Source/Collision/CollisionShapes/CollisionRect.h"

class Item;
class Entity;

class ItemsComponent : public Node2D {
private:
	int currentItemIndex = -1;

public:
	ItemsComponent(bool actAsWeaponInventory = false, Entity* owner = nullptr, std::string name = "ItemsComponent");

	bool actAsWeaponInventory = false;

	Signal<Item*> pickup;
	Signal<Item*> item_switched;
	Signal<Item*> used;

	Entity* owner = nullptr;

	List<Item*> items;

	CollisionBody* itemPickupArea = new CollisionBody();
	CollisionRect* itemPickupShape = new CollisionRect();


	void ready() override;
	void update(float delta) override;
	void physicsUpdate(float delta) override;


	void onItemPickup(Item* item);
	void useCurrentItem();

	void nextItem();
	Item* getCurrentItem();
	int getCurrentItemIndex();

};

#include "Source/Items/Item.h"
#include "Source/Entities/Entity.h"