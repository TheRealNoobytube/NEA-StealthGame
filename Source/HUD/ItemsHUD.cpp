#include "ItemsHUD.h"


ItemsHUD::ItemsHUD(std::string name) : Node2D(name){
	addChild(itemsBG);
	addChild(itemIcon);
	itemIcon->ignoreRenderOffset = true;
	addChild(weaponsBG);
	addChild(weaponIcon);
	weaponIcon->ignoreRenderOffset = true;

	addChild(itemQuantityText);

	Item* tempItem = new Item();

	itemIcon->setHFrames(tempItem->sprite->getHFrames());
	itemIcon->setVFrames(tempItem->sprite->getVFrames());

	weaponIcon->setHFrames(tempItem->sprite->getHFrames());
	weaponIcon->setVFrames(tempItem->sprite->getVFrames());

	delete tempItem;
}

void ItemsHUD::ready() {
	__super::ready();

	int animationSpeed = 8;

	itemIcon->scale = Vector2D(2, 2);
	itemIcon->position.x = 2;
	itemIcon->position.y = getSceneTree()->getViewportSize().y - 35;

	itemIcon->setTexture(getSceneTree()->getBasePath() + "../Assets/Items/Items.png");
	itemIcon->visible = false;

	weaponIcon->scale = Vector2D(2, 2);
	weaponIcon->position.x = getSceneTree()->getViewportSize().x - 35;
	weaponIcon->position.y = getSceneTree()->getViewportSize().y - 35;

	weaponIcon->setTexture(getSceneTree()->getBasePath() + "../Assets/Items/Items.png");
	weaponIcon->visible = false;



	itemsBG->setTexture(getSceneTree()->getBasePath() + "../Assets/Items/ItemUI.png");
	itemsBG->ignoreRenderOffset = true;
	itemsBG->setHFrames(3);

	itemsBG->position.y = getSceneTree()->getViewportSize().y - itemsBG->getTexture()->getDimensions().y;
	itemsBG->createAnimation("ItemSwitch", { 1, 0 }, animationSpeed);
	itemsBG->stop();

	itemsBG->animationFinished.connect([this]() { onItemsBGAnimationFinished(); });

	itemQuantityText->position.x = 38;
	itemQuantityText->color = Color(255, 255, 255);
	itemQuantityText->position.y = getSceneTree()->getViewportSize().y - 30;
	itemQuantityText->scale = Vector2D(0.5, 0.5);
	itemQuantityText->setFontSize(20);
	itemQuantityText->text = "01";
	itemQuantityText->visible = false;

	weaponsBG->setTexture(getSceneTree()->getBasePath() + "../Assets/Items/ItemUI.png");
	weaponsBG->ignoreRenderOffset = true;
	weaponsBG->setHFrames(3);
	weaponsBG->flipH = true;

	weaponsBG->position.x = getSceneTree()->getViewportSize().x - (itemsBG->getTexture()->getDimensions().x / itemsBG->getHFrames());
	weaponsBG->position.y = getSceneTree()->getViewportSize().y - (itemsBG->getTexture()->getDimensions().y / itemsBG->getVFrames());
	weaponsBG->createAnimation("WeaponSwitch", { 1, 0 }, animationSpeed, true);
	weaponsBG->stop();

	weaponsBG->animationFinished.connect([this]() { onWeaponsBGAnimationFinished(); });
}

void ItemsHUD::update(float delta) {
	__super::update(delta);

}

void ItemsHUD::hideItemIcon() {
	itemIcon->visible = false;
	itemQuantityText->visible = false;
}

void ItemsHUD::hideWeaponIcon() {
	weaponIcon->visible = false;
}

void ItemsHUD::changeItemIcon(Item* item, bool playAnimation) {
	if (playAnimation) {
		itemIcon->visible = false;
		itemsBG->play("ItemSwitch");
	}
	else {
		itemIcon->visible = true;
	}


	if (item->stackable) {
		if (item->getQuantity() <= 0) {
			showItemQuantity = false;
		}
		else {
			itemQuantityText->text = std::to_string(item->getQuantity());
			showItemQuantity = true;
		}
	}
	else {
		showItemQuantity = false;
	}

	if (showItemQuantity && !playAnimation) {
		itemQuantityText->visible = true;
	}
	else {
		itemQuantityText->visible = false;
	}

	itemIcon->frame = item->getItemID();
}

void ItemsHUD::changeWeaponIcon(Item* weapon, bool playAnimation) {
	if (playAnimation) {
		weaponIcon->visible = false;
		weaponsBG->play("WeaponSwitch");
	}
	else {
		weaponIcon->visible = true;
	}

	weaponIcon->frame = weapon->getItemID();
}


void ItemsHUD::onItemsBGAnimationFinished() {
	itemIcon->visible = true;

	if (showItemQuantity) {
		itemQuantityText->visible = true;
	}
}

void ItemsHUD::onWeaponsBGAnimationFinished() {
	weaponIcon->visible = true;
}


bool ItemsHUD::showingItem() {
	return itemIcon->visible;
}

int ItemsHUD::getCurrentItemID() {
	return itemIcon->frame;
}

bool ItemsHUD::showingWeapon() {
	return weaponIcon->visible;
}

int ItemsHUD::getCurrentWeaponID() {
	return weaponIcon->frame;
}