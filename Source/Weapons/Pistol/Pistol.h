#pragma once
#include "Source/Items/Item.h"

class Pistol : public Item {
public:
	Pistol(std::string name = "Pistol");

	void ready() override;
	void update(float delta) override;
};