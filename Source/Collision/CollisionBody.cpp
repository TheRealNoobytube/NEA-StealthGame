#include "CollisionBody.h"


CollisionBody::CollisionBody(std::string name) : Collision(name){

}

void CollisionBody::ready() {
	__super::ready();
	getSceneTree()->addToCollisionBodies(this);
}

void CollisionBody::update(float delta) {
	__super::update(delta);

}


List<CollisionData> CollisionBody::requestCollisions() {
	List<CollisionData> collisionData;

	List<Node*> bodies = getSceneTree()->getCollisionBodies();


	for (int j = 0; j < shapes.getSize(); j++) {

		CollisionRect* rect = reinterpret_cast<CollisionRect*>(shapes.get(j));

		if (rect->disabled) {
			continue;
		}


		for (int i = 0; i < bodies.getSize(); i++) {
			CollisionBody* body = reinterpret_cast<CollisionBody*>(bodies.get(i));

			if (body == this) {
				continue;
			}

			if (!(body->layer & (mask))) {
				continue;
			}

			CollisionData data = rect->detectCollisions(body);

			if (data.colliding) {
				collisionData.add(data);
			}
		}
	}

	return collisionData;
}


void CollisionBody::addCollisionShape(CollisionShape* shape) {
	shapes.add(shape);
}

List<CollisionShape*> CollisionBody::getCollisionShapes() {
	return shapes;
}