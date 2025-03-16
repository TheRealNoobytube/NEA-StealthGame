#include "HealthComponent.h"



HealthComponent::HealthComponent(Entity* entity, std::string name) {
	this->entity = entity;
}

void HealthComponent::dealDamage(float damage) {
	health -= damage;
	damaged.emit(damage);

	if (health <= 0) {
		death.emit(damage);
	}
}

void HealthComponent::heal(float amount, bool overHeal) {
	health += amount;

	if (!overHeal) {
		if (health > maxHealth) {
			health = maxHealth;
		}
	}
}

void HealthComponent::setMaxHealth(float maxHealth, bool updateHealth) {
	this->maxHealth = maxHealth;

	if (maxHealth < health || updateHealth) {
		health = maxHealth;
	}

}

float HealthComponent::getMaxHealth() {
	return maxHealth;
}

float HealthComponent::getHealth() {
	return this->health;
}