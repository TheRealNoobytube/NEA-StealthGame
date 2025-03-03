#pragma once
#include "Source/Projectiles/Projectile.h"

class PistolShot : public Projectile {


public:
	PistolShot(std::string name = "PistolShot");

	void ready() override;

};