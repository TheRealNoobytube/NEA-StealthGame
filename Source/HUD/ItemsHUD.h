#pragma once
#include "Source/UI/Button/Button.h"
#include "Source/Nodes/AnimatedSprite/AnimatedSprite.h"
#include "Source/Items/Item.h"


class ItemsHUD : public Node2D {
private:
	Label* itemQuantityText = new Label();

	bool showItemQuantity = false;

public:
	ItemsHUD(std::string name = "ItemsHUD");

	AnimatedSprite* itemsBG = new AnimatedSprite();
	Sprite* itemIcon = new Sprite();
	AnimatedSprite* weaponsBG = new AnimatedSprite();
	Sprite* weaponIcon = new Sprite();

	void ready() override;
	void update(float delta) override;


	void hideHUD();

	void hideItemIcon();
	void hideWeaponIcon();
	void changeItemIcon(Item* item, bool playAnimation = true);
	void changeWeaponIcon(Item* weapon, bool playAnimation = true);

	bool showingItem();
	bool showingWeapon();

	int getCurrentItemID();
	int getCurrentWeaponID();
	//void addToHUD(Item* item);
	//bool showOnHUD(Item* item, bool playAnimation = true, bool isWeapon = false);
	//void updateItemHUD();
	////void updateWeaponHUD();

	void onItemsBGAnimationFinished();
	void onWeaponsBGAnimationFinished();
};