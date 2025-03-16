#include "Item.h"

Item::Item(std::string name) : CollisionBody(name){
	addChild(sprite);
	addChild(pickupRange);
	addChild(useTimer);
	sprite->setHFrames(4);
	sprite->setVFrames(2);
}

Item::Item(Item& item) {
	addChild(useTimer);

	owner = item.owner;
	useSpeed = item.useSpeed;
	stackable = item.stackable;
	consumable = item.consumable;
	sprite->frame = item.getItemID();
	isWeapon = item.isWeapon;
	item.consumable = consumable;
}


void Item::ready() {
	__super::ready();
	sprite->position = Vector2D(-8, -8);
	layer = ITEMS;

	pickupRange->setSize(Vector2D(12, 12));
	pickupRange->position = Vector2D(-6, -6);
	pickupRange->testColor = Color(120, 120, 255, 120);
	pickupRange->visible = false;

	sprite->setTexture(getSceneTree()->getBasePath() + "../Assets/Items/Items.png");

	useTimer->loop = false;
}

void Item::update(float delta) {
	__super::update(delta);

}

void Item::equip(Entity* owner) {
	this->owner = owner;
	equipped = true;
	onEquip();
}

void Item::onEquip() {}


void Item::remove() {
	this->owner = nullptr;
	equipped = false;
	onRemove();
}

void Item::onRemove() {}


bool Item::use() {
	if (onCooldown()) {
		return false;
	}

	useTimer->setLength(useSpeed);
	useTimer->start();

	if (consumable) {
		quantity -= 1;
	}

	onUse();

	return true;
}

void Item::onUse() {}




bool Item::isEquipped() {
	return equipped;
}


void Item::addQuantity(int quantity) {
	this->quantity += quantity;
}

void Item::removeQuantity(int quantity) {
	this->quantity -= quantity;
}

void Item::setQuantity(int quantity) {
	this->quantity = quantity;
}

int Item::getQuantity() {
	return quantity;
}


float Item::getItemID() {
	return sprite->frame;
}


bool Item::onCooldown() {
	return useTimer->isRunning();
}
