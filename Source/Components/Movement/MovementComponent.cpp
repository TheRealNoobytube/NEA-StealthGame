#include "MovementComponent.h"

MovementComponent::MovementComponent(Entity* entity, std::string name) : Node2D(name) {
	this->entity = entity;
	addChild(sweptRaycast);
	sweptRaycast->visible = false;
}

void MovementComponent::ready() {

}

void MovementComponent::update(float delta) {

}

List<CollisionData> MovementComponent::applyVelocity() {
	if (velocity == Vector2D(0, 0)) {
		return false;
	}

	if (direction.x != 0 || direction.y != 0) {
		lookingDirection = direction;
	}

	sweptRaycast->targetPosition = velocity;
	sweptRaycast->mask = entity->mask;

	Vector2D oldVelocity = velocity;

	List<CollisionData> data = findCollisions();

	entity->position.x += velocity.x;
	entity->position.y += velocity.y;

	return data;
}

List<CollisionData> MovementComponent::findCollisions() {


	List<CollisionData> collisionData;

	List<Node*> bodies = getSceneTree()->getCollisionBodies();


	for (int j = 0; j < entity->getCollisionShapes().getSize(); j++) {

		CollisionRect* entityRect = reinterpret_cast<CollisionRect*>(entity->getCollisionShapes().get(j));

		if (entityRect->disabled) {
			continue;
		}

		for (int i = 0; i < bodies.getSize(); i++) {
			CollisionBody* body = reinterpret_cast<CollisionBody*>(bodies.get(i));

			if (body == entity) {
				continue;
			}

			if (!(body->layer & (entity->mask))) {
				continue;
			}


			for (int k = 0; k < body->getCollisionShapes().getSize(); k++) {

				CollisionRect* bodyRect = reinterpret_cast<CollisionRect*>(body->getCollisionShapes().get(k));

				sweptRaycast->position = entityRect->position;
				sweptRaycast->position.x += entityRect->getSize().x / 2;
				sweptRaycast->position.y += entityRect->getSize().y / 2;

				CollisionRect tempRect;

				tempRect.position = bodyRect->getGlobalPosition();
				tempRect.position.x -= entityRect->getSize().x / 2;
				tempRect.position.y -= entityRect->getSize().y / 2;

				tempRect.setSize(Vector2D(bodyRect->getSize().x + entityRect->getSize().x, bodyRect->getSize().y + entityRect->getSize().y));

				sweptRaycast->checkAgainstRect(&tempRect);

				if (sweptRaycast->isColliding()) {
					collisionData.add(CollisionData(true, sweptRaycast->getIntersectionPoint(), body));
					velocity.x += abs(velocity.x) * (1 - sweptRaycast->getContactTime()) * sweptRaycast->getContactNormal().x;
					velocity.y += abs(velocity.y) * (1 - sweptRaycast->getContactTime()) * sweptRaycast->getContactNormal().y;
				}
			}
		}
	}


	return collisionData;








	/*auto body = dynamic_cast<CollisionBody*>(node);

	if (body != nullptr && body != entity && body->layer & (entity->mask)) {

		for (int i = 0; i < body->getChildCount(); i++) {

			auto bodyShape = dynamic_cast<CollisionRect*>(node->getChild(i));

			if (bodyShape != nullptr && !bodyShape->disabled) {

				for (int j = 0; j < entity->getChildCount(); j++) {

					auto entityShape = dynamic_cast<CollisionRect*>(entity->getChild(j));

					if (entityShape != nullptr) {
						sweptRaycast->position = entityShape->position;
						sweptRaycast->position.x += entityShape->getSize().x / 2;
						sweptRaycast->position.y += entityShape->getSize().y / 2;

						CollisionRect tempRect;

						tempRect.position = bodyShape->getGlobalPosition();
						tempRect.position.x -= entityShape->getSize().x / 2;
						tempRect.position.y -= entityShape->getSize().y / 2;

						tempRect.setSize(Vector2D(bodyShape->getSize().x + entityShape->getSize().x, bodyShape->getSize().y + entityShape->getSize().y));

						sweptRaycast->checkAgainstRect(&tempRect);

						if (sweptRaycast->isColliding()) {
							data->add(CollisionData(true, sweptRaycast->getIntersectionPoint(), body));
							velocity.x += abs(velocity.x) * (1 - sweptRaycast->getContactTime()) * sweptRaycast->getContactNormal().x;
							velocity.y += abs(velocity.y) * (1 - sweptRaycast->getContactTime()) * sweptRaycast->getContactNormal().y;
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < node->getChildCount(); i++) {
		findCollisions(node->getChild(i), data);
	}*/
}

Vector2D MovementComponent:: getLookingDirection() {
	return lookingDirection;
}