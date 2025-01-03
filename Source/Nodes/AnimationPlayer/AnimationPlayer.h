#pragma once
#include "Source/Nodes/TimerNode/TimerNode.h"
#include "Animation.h"

class AnimationPlayer : public Node {
private:
	TimerNode animationTimer;
	List<Animation*> animations;
	List<std::string> keys;

	Animation* currentAnimation;
	int frame;

public:
	AnimationPlayer(std::string name = "AnimationPlayer");

	void addAnimation(Animation* animation);
	Animation* getAnimation(std::string name);
	void removeAnimation(std::string name);

	void play(std::string name);

	void ready() override;
	void update(float delta) override;
};