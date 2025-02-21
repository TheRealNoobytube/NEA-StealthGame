#include "MovementComponent.h"

MovementComponent::MovementComponent(Entity* entity, std::string name) : Node2D(name) {
	this->entity = entity;
	addChild(&sweptRaycast);
	sweptRaycast.visible = false;
}

void MovementComponent::ready() {

}

void MovementComponent::update(float delta) {

}

bool MovementComponent::applyVelocity() {
	if (velocity == Vector2D(0, 0)) {
		return false;
	}

	sweptRaycast.targetPosition = velocity;
	sweptRaycast.mask = entity->mask;

	Vector2D initialVelocity = velocity;

	List<CollisionData> data;

	findCollisions(getSceneTree()->getRoot(), &data);
	entity->position.x += velocity.x;
	entity->position.y += velocity.y;

	return !data.isEmpty();
}

void MovementComponent::findCollisions(Node* node, List<CollisionData>* data) {

	auto body = dynamic_cast<CollisionBody*>(node);

	if (body != nullptr && body != entity) {

		for (int i = 0; i < body->getChildCount(); i++) {

			auto bodyShape = dynamic_cast<CollisionRect*>(node->getChild(i));

			if (bodyShape != nullptr) {

				for (int j = 0; j < entity->getChildCount(); j++) {

					auto entityShape = dynamic_cast<CollisionRect*>(entity->getChild(j));

					if (entityShape != nullptr) {
						sweptRaycast.position = entityShape->position;
						sweptRaycast.position.x += entityShape->getSize().x / 2;
						sweptRaycast.position.y += entityShape->getSize().y / 2;

						CollisionRect tempRect;

						tempRect.position = bodyShape->getGlobalPosition();
						tempRect.position.x -= entityShape->getSize().x / 2;
						tempRect.position.y -= entityShape->getSize().y / 2;

						tempRect.setSize(Vector2D(bodyShape->getSize().x + entityShape->getSize().x, bodyShape->getSize().y + entityShape->getSize().y));

						sweptRaycast.checkAgainstRect(&tempRect);

						if (sweptRaycast.isColliding()) {
							data->add(CollisionData(true, sweptRaycast.getIntersectionPoint(), body));
							velocity.x += abs(velocity.x) * (1 - sweptRaycast.contactTime) * sweptRaycast.getContactNormal().x;
							velocity.y += abs(velocity.y) * (1 - sweptRaycast.contactTime) * sweptRaycast.getContactNormal().y;
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < node->getChildCount(); i++) {
		findCollisions(node->getChild(i), data);
	}
}