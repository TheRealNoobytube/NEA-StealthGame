#pragma once
#include "Source/Entities/Entity.h"
#include "Source/Nodes/Sprite/Sprite.h"

class Item : public CollisionBody {
private:

	TimerNode* useTimer = new TimerNode();

	bool equipped = false;
	int quantity = 0;

protected:
	virtual void onEquip();
	virtual void onRemove();
	virtual void onUse();

public:
	Item(std::string name = "Item");

	Item(Item& item);


	Entity* owner;

	CollisionRect* pickupRange = new CollisionRect();
	Sprite* sprite = new Sprite();


	bool isWeapon = false;
	bool consumable = true;
	bool stackable = false;

	float useSpeed = 1;

	float damage = 1;

	void ready() override;
	void update(float delta) override;


	void addQuantity(int quantity);
	void removeQuantity(int quantity);
	void setQuantity(int quantity);
	int getQuantity();

	void equip(Entity* owner);
	void remove();
	bool use();

	bool isEquipped();

	float getItemID();

	void setUseSpeed(float speed);

	bool onCooldown();
};

