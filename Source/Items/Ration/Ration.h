#pragma once
#include "Source/Items/Item.h"

class Ration : public Item {
public:
	Ration(std::string name = "Ration");

	void ready() override;
};