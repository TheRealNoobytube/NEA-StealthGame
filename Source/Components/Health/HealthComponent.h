#pragma once
#include "Source/Nodes/Node.h"

class Entity;

class HealthComponent : public Node {
private:
	float maxHealth = 10;
	float health = maxHealth;

public:
	Signal<float> damaged;
	Signal<float> death;


	Entity* entity;

	HealthComponent(Entity* entity, std::string name = "HealthComponent");

	void dealDamage(float damage);

	void setMaxHealth(float maxHealth, bool updateHealth = false);
	float getHealth();

};

#include "Source/Entities/Entity.h"