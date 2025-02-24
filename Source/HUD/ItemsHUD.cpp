#include "ItemsHUD.h"


ItemsHUD::ItemsHUD(std::string name) : Node2D(name){
	addChild(&itemsBG);
	addChild(&weaponsBG);
	addChild(&itemQuantityText);
}

void ItemsHUD::ready() {
	__super::ready();

	int animationSpeed = 8;

	
	itemsBG.setTexture(getSceneTree()->getBasePath() + "../Assets/Items/ItemUI.png");
	itemsBG.ignoreRenderOffset = true;
	itemsBG.setHFrames(3);

	itemsBG.position.y = getSceneTree()->getViewportSize().y - itemsBG.getTexture()->getDimensions().y;
	itemsBG.createAnimation("ItemSwitch", { 1, 0 }, animationSpeed);

	itemsBG.animationFinished.connect([this]() { onItemsBGAnimationFinished(); });

	itemQuantityText.position.x = 38;
	itemQuantityText.color = Color(255, 255, 255);
	itemQuantityText.position.y = getSceneTree()->getViewportSize().y - 30;
	itemQuantityText.scale = Vector2D(0.5, 0.5);
	itemQuantityText.setFontSize(20);
	itemQuantityText.text = "01";
	itemQuantityText.visible = false;

	weaponsBG.setTexture(getSceneTree()->getBasePath() + "../Assets/Items/ItemUI.png");
	weaponsBG.ignoreRenderOffset = true;
	weaponsBG.setHFrames(3);
	weaponsBG.flipH = true;

	weaponsBG.position.x = getSceneTree()->getViewportSize().x - (itemsBG.getTexture()->getDimensions().x / itemsBG.getHFrames());
	weaponsBG.position.y = getSceneTree()->getViewportSize().y - (itemsBG.getTexture()->getDimensions().y / itemsBG.getVFrames());
	weaponsBG.createAnimation("WeaponSwitch", { 1, 0 }, animationSpeed, true);

	weaponsBG.animationFinished.connect([this]() { onWeaponsBGAnimationFinished(); });
}

void ItemsHUD::update(float delta) {
	__super::update(delta);

}


void ItemsHUD::addToHUD(Item* item) {
	if (item->getParent() != nullptr) {
		item->getParent()->removeChild(item);
	}

	addChild(item);

	item->sprite.ignoreRenderOffset = true;
	item->pickupRange.disabled = true;

	item->sprite.scale = Vector2D(2, 2);
	item->position.y = getSceneTree()->getViewportSize().y - 26;

	if (!item->isWeapon) {
		item->position.x = 12;
		if (currentItem == nullptr) {
			currentItem = item;
			updateItemHUD();
		}
		else {
			item->sprite.visible = false;
		}
	}
	else {
		item->position.x = getSceneTree()->getViewportSize().x - 26;
		if (currentWeapon == nullptr) {
			currentWeapon = item;
			updateWeaponHUD();
		}
		else {
			item->sprite.visible = false;
		}
	}


}

bool ItemsHUD::showOnHUD(Item* item, bool playAnimation, bool isWeapon) {
	if (item == nullptr) {
		if (isWeapon) {
			currentWeapon->sprite.visible = false;
			currentWeapon = nullptr;
		}
		else {
			currentItem->sprite.visible = false;
			currentItem = nullptr;
		}

		return true;
	}

	if (item->isWeapon) {
		if (nextWeapon != nullptr) {
			return false;
		}

		currentWeapon->sprite.visible = false;
		nextWeapon = item;

		if (playAnimation) {
			weaponsBG.play("WeaponSwitch");
		}
		else {
			onItemsBGAnimationFinished();
		}

		return true;
	}
	else {
		if (nextItem != nullptr) {
			return false;
		}

		currentItem->sprite.visible = false;
		nextItem = item;

		itemQuantityText.visible = false;

		if (playAnimation) {
			itemsBG.play("ItemSwitch");
		}
		else {
			onItemsBGAnimationFinished();
		}

		return true;
	}
}


void ItemsHUD::updateItemHUD() {
	if (currentItem == nullptr) {
		return;
	}

	currentItem->sprite.visible = true;

	if (currentItem->stackable) {
		if (currentItem->getQuantity() > 0) {
			itemQuantityText.visible = true;
			itemQuantityText.text = std::to_string(currentItem->getQuantity());
		}
		else {
			itemQuantityText.visible = false;
		}
	}
	else {
		itemQuantityText.visible = false;
	}
}

void ItemsHUD::updateWeaponHUD() {
	if (currentWeapon == nullptr) {
		return;
	}

	currentWeapon->sprite.visible = true;
}



void ItemsHUD::onItemsBGAnimationFinished() {
	currentItem = nextItem;
	nextItem = nullptr;

	updateItemHUD();
}

void ItemsHUD::onWeaponsBGAnimationFinished() {
	currentWeapon = nextWeapon;
	nextWeapon = nullptr;

	updateWeaponHUD();
}