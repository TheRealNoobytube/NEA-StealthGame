#pragma once

#include "Source/Nodes/AnimatedSprite/AnimatedSprite.h"
#include "Source/Collision/CollisionBody.h"
#include "Source/Collision/CollisionShapes/CollisionRect.h"
#include "Source/Components/Movement/MovementComponent.h"



class Entity : public CollisionBody {
public:
	Entity(std::string name = "Entity");
};