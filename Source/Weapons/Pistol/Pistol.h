#pragma once
#include "Source/Items/Item.h"
#include "Source/Projectiles/PistolShot/PistolShot.h"
#include "Source/Scenes/Levels/Level.h"

class Pistol : public Item {
public:
	Pistol(std::string name = "Pistol");

	void ready() override;
	void update(float delta) override;

	void onUse() override;

};