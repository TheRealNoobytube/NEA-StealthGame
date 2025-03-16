#pragma once
#include "Source/Items/Item.h"

class Ration : public Item {
public:
	Ration(std::string name = "Ration");

	float healingAmount = 2;

	void ready() override;

	void onUse() override;
};