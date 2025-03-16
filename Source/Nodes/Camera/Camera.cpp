#include "Camera.h"


Camera::Camera(std::string name) : Node2D(name){

}


void Camera::ready() {
	__super::ready();

	if (enabled) {
		calculateTargetPosition();
		skipToTargetPosition();
	}
}


void Camera::onSceneTreeExited() {
	getSceneTree()->setRenderOffset(Vector2D(0, 0));
}

void Camera::physicsUpdate(float delta) {
	__super::physicsUpdate(delta);
	if (enabled) {
		calculateTargetPosition();

		Vector2D renderOffset = getSceneTree()->getRenderOffset();
		position.x = linearInterpolate(renderOffset.x, targetPosition.x, delta * cameraSpeed);
		position.y = linearInterpolate(renderOffset.y, targetPosition.y, delta * cameraSpeed);

		getSceneTree()->setRenderOffset(position);
	}
}


void Camera::calculateTargetPosition() {
	targetPosition = static_cast<Node2D*>(getParent())->position;
	targetPosition.x = -targetPosition.x + (getSceneTree()->getViewportSize().x / 2) + offset.x;
	targetPosition.y = -targetPosition.y + (getSceneTree()->getViewportSize().y / 2) + offset.y;
}

void Camera::skipToTargetPosition() {
	position = targetPosition;
	getSceneTree()->setRenderOffset(position);
}

void Camera::setCameraSpeed(float speed) {
	if (speed <= 0) {
		speed = 0.1;
	}
	this->cameraSpeed = speed;
}

float Camera::getCameraSpeed() {
	return cameraSpeed;
}