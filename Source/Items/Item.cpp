#include "Item.h"

Item::Item(std::string name) : CollisionBody(name){
	addChild(&sprite);
	addChild(&pickupRange);
}

void Item::ready() {
	__super::ready();
	sprite.position = Vector2D(-8, -8);
	layer = ITEMS;

	pickupRange.setSize(Vector2D(12, 12));
	pickupRange.position = Vector2D(-6, -6);
	pickupRange.testColor = Color(120, 120, 255, 120);
	pickupRange.visible = false;


	sprite.setTexture(getSceneTree()->getBasePath() + "../Assets/Items/Items.png");
	sprite.setHFrames(4);
	sprite.setVFrames(2);
}

void Item::update(float delta) {
	__super::update(delta);

}

void Item::equip() {
	equipped = true;
	onEquip();
}

void Item::onEquip() {}


void Item::remove() {
	equipped = false;
	onRemove();
}

void Item::onRemove() {}

void Item::use() {
	if (consumable) {
		quantity -= 1;
	}
}



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
	return sprite.frame;
}