#pragma once
#include "Source/UI/Button/Button.h"
#include "Source/Nodes/AnimatedSprite/AnimatedSprite.h"
#include "Source/Items/Item.h"


class ItemsHUD : public Node2D {
private:
	Label itemQuantityText;

	Item* nextItem = nullptr;
	Item* currentItem = nullptr;

	Item* nextWeapon = nullptr;
	Item* currentWeapon = nullptr;

public:
	ItemsHUD(std::string name = "ItemsHUD");

	AnimatedSprite itemsBG;
	AnimatedSprite weaponsBG;

	void ready() override;
	void update(float delta) override;

	void addToHUD(Item* item);
	bool showOnHUD(Item* item, bool playAnimation = true, bool isWeapon = false);
	void updateItemHUD();
	void updateWeaponHUD();

	void onItemsBGAnimationFinished();
	void onWeaponsBGAnimationFinished();
};