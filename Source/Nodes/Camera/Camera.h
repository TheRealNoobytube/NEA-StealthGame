#pragma once
#include "Source/Nodes/Node2D/Node2D.h"

class Camera : public Node2D {
private:

	Vector2D targetPosition = Vector2D(0, 0);
	float cameraSpeed = 8;

public:
	Camera(std::string name = "Camera");

	Vector2D offset = Vector2D(0, 0);

	bool enabled = true;

	void ready() override;
	void physicsUpdate(float delta) override;

	void onSceneTreeExited() override;

	//finds the new target position based on the camera's parent's current position in the Scene
	void calculateTargetPosition();
	//skips the camera smoothing done and goes straight to the target position
	void skipToTargetPosition();
	
	void setCameraSpeed(float speed);
	float getCameraSpeed();
};
