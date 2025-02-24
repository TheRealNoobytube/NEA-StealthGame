#pragma once
#include "Source/Collision/CollisionBody.h"
#include "Source/Nodes/Sprite/Sprite.h"

class Item : public CollisionBody {
private:

	bool equipped = false;
	int quantity = 0;

protected:
	void onEquip();
	void onRemove();
	void onUse();

public:
	Item(std::string name = "Item");

	bool isWeapon = false;
	bool consumable = true;
	bool stackable = false;

	CollisionRect pickupRange;
	Sprite sprite;

	void ready() override;
	void update(float delta) override;


	void addQuantity(int quantity);
	void removeQuantity(int quantity);
	void setQuantity(int quantity);
	int getQuantity();

	void equip();
	void remove();
	void use();

	bool isEquipped();

	float getItemID();
};

