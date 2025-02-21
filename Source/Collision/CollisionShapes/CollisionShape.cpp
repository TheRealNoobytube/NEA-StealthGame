#include "CollisionShape.h"


CollisionShape::CollisionShape(std::string name) : Node2D(name){

}

void CollisionShape::ready() {
	__super::ready();
}

void CollisionShape::update(float delta) {
	__super::update(delta);

}
CollisionData CollisionShape::detectCollisions(CollisionBody* body){
	return CollisionData();
}