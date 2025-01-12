#include "Entity.h"



Entity::Entity(std::string name) : CollisionBody(name) {
	layer = ENTITIES;
	mask = WORLD | ENTITIES;
}