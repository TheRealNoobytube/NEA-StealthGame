#pragma once
#include "Source/Nodes/Sprite/Sprite.h"
#include "Source/Nodes/TimerNode/TimerNode.h"

class AnimatedSprite : public Sprite{
private:
	struct Animation{
		std::string name;
		List<int> frames;
		int fps;
		bool loop;


		Animation() {}

		Animation(std::string name, List<int> frames, int fps, bool loop) {
			this->name = name;
			this->frames = frames;
			this->fps = fps;
			this->loop = loop;
		}
	};

	List<Animation> animations;

	bool loop = false;
	int fps = 10;
	int currentAnimationIndex;
	int currentFrameIndex;

	TimerNode animationTimer;

	Animation* getAnimation(std::string name);

public:
	AnimatedSprite(std::string filepath = "", std::string name = "AnimatedSprite");
	AnimatedSprite(Texture* texture, std::string name = "AnimatedSprite");

	void createAnimation(std::string name, List<int> frames, int fps = 10, bool loop = false);
	void changeAnimation(std::string name, List<int> frames);

	void play(std::string name, bool restart = false);

	void animationTimerTimeout();

	void setFps(int fps);
	int getFps();

	int findAnimationIndex(std::string name);

	void ready() override;
	void update(float delta) override;
	




};