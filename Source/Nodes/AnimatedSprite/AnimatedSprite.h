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
		bool flipH;
		bool flipV;

		Animation() {}

		Animation(std::string name, List<int> frames, bool flipH, bool flipV, int fps, bool loop) {
			this->name = name;
			this->frames = frames;
			this->fps = fps;
			this->loop = loop;
			this->flipH = flipH;
			this->flipV = flipV;
		}
	};

	List<Animation> animations;

	bool loop = false;
	float speedScale = 1;
	int fps = 10;
	int currentAnimationIndex = -1;
	int currentFrameIndex;

	TimerNode* animationTimer = new TimerNode();

	Animation* getAnimation(std::string name);

public:
	Signal<> animationFinished;

	AnimatedSprite(std::string filepath = "", std::string name = "AnimatedSprite");
	AnimatedSprite(Texture* texture, std::string name = "AnimatedSprite");

	void createAnimation(std::string name, List<int> frames, int fps = 10, bool flipH = false, bool flipV = false,  bool loop = false);
	void changeAnimation(std::string name, List<int> frames);

	void play(std::string name, bool restart = false);
	void stop();

	void animationTimerTimeout();

	void setFps(int fps);
	int getFps();

	void setSpeedScale(float speedScale);
	float getSpeedScale();

	int findAnimationIndex(std::string name);

	void ready() override;
	void update(float delta) override;
	
	bool isPlaying();

	std::string getAnimationName();



};