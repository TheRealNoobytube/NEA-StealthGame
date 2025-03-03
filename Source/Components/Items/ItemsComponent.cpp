#include "ItemsComponent.h"

ItemsComponent::ItemsComponent(bool actAsWeaponInventory, Entity* owner, std::string name) : Node2D(name){
	addChild(itemPickupArea);
	itemPickupArea->addChild(itemPickupShape);
	this->actAsWeaponInventory = actAsWeaponInventory;
	this->owner = owner;
}


void ItemsComponent::ready() {
	__super::ready();
	itemPickupShape->setSize(Vector2D(18, 18));
	itemPickupShape->position = Vector2D(-itemPickupShape->getSize().x / 2, -itemPickupShape->getSize().y / 2);
	itemPickupShape->testColor = Color(120, 120, 255, 120);
	itemPickupShape->visible = false;

	itemPickupArea->layer = 0;
	itemPickupArea->mask = Entity::ITEMS;
}


void ItemsComponent::update(float delta) {
	__super::update(delta);
}

void ItemsComponent::physicsUpdate(float delta) {
	__super::physicsUpdate(delta);

	List<CollisionData> data = itemPickupArea->requestCollisions();

	if (!data.isEmpty()) {
		for (int i = 0; i < data.getSize(); i++) {
			Item* item = reinterpret_cast<Item*>(data.get(i).body);

			onItemPickup(item);
		}
	}
}






void ItemsComponent::onItemPickup(Item* item) {
	if (item->isWeapon) {
		if (!actAsWeaponInventory) {
			return;
		}
	}
	else {
		if (actAsWeaponInventory) {
			return;
		}
	}

	for (int i = 0; i < items.getSize(); i++) {
		if (item->getItemID() == items.get(i)->getItemID()) {
			if (item->stackable) {
				items.get(i)->addQuantity(1);
				item->queueFree();
				pickup.emit(items.get(i));
			}
			return;
		}
	}


	if (item->stackable) {
		item->addQuantity(1);
	}

	if (currentItemIndex == -1) {
		currentItemIndex = 0;
	}

	item->equip(owner);
	items.add(item);
	item->sprite->visible = false;
	item->pickupRange->disabled = true;
	pickup.emit(item);
}

void ItemsComponent::useCurrentItem() {
	if (currentItemIndex == -1) {
		return;
	}

	Item* item = items.get(currentItemIndex);

	if (!item->use()) {
		return;
	}

	if (item->consumable) {
		if (item->stackable) {
			if (item->getQuantity() <= 0) {
				items.remove(currentItemIndex);

				if (items.getSize() > 0) {
					currentItemIndex = items.getSize() - 1;
				}
				else {
					currentItemIndex = -1;
				}
			}
		}
	}

	used.emit(items.get(currentItemIndex));
}

void ItemsComponent::nextItem() {
	if (currentItemIndex == -1) {
		return;
	}

	currentItemIndex = (currentItemIndex + 1) % items.getSize();
	item_switched.emit(items.get(currentItemIndex));
}

Item* ItemsComponent::getCurrentItem() {
	if (currentItemIndex > items.getSize() - 1) {
		return nullptr;
	}

	return items.get(currentItemIndex);
}

int ItemsComponent::getCurrentItemIndex() {
	return currentItemIndex;
}