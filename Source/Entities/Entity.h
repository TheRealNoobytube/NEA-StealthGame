#pragma once

#include "Source/Nodes/AnimatedSprite/AnimatedSprite.h"
#include "Source/Collision/Raycast/Raycast.h"
#include "Source/Collision/CollisionBody.h"
#include "Source/Collision/CollisionShapes/CollisionRect.h"
#include "Source/Components/Movement/MovementComponent.h"
#include "Source/Items/Item.h"

class Entity : public CollisionBody {
public:
	Entity(std::string name = "Entity");

	MovementComponent movement = MovementComponent(this);
	float speed;
};

