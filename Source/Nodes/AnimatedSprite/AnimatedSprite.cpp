#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(std::string filepath, std::string name) : Sprite(filepath, name) {
	addChild(&animationTimer);
}

AnimatedSprite::AnimatedSprite(Texture* texture, std::string name) : Sprite(texture, name) {
	addChild(&animationTimer);
}


void AnimatedSprite::ready() {
	__super::ready();
	animationTimer.loop = false;

	animationTimer.timeout.connect([this]() { animationTimerTimeout(); });
	setFps(fps);
}

void AnimatedSprite::update(float delta) {
	__super::update(delta);
}



void AnimatedSprite::createAnimation(std::string name, List<int> frames, int fps, bool flipH, bool flipV, bool loop) {
	if (getAnimation(name) != nullptr) { //if the animation name already exists, update the animation instead
		changeAnimation(name, frames);
	}
	else {
		animations.add(Animation(name, frames, flipH, flipV, fps, loop));
	}
}

void AnimatedSprite::changeAnimation(std::string name, List<int> frames) {
	getAnimation(name)->name = name;
	getAnimation(name)->frames = frames;
}

void AnimatedSprite::play(std::string name, bool restart) {
	int index = findAnimationIndex(name);
	if (index == -1) {
		std::cout << "Animation " << name << " not found in List\n";
		return;
	}

	if (currentAnimationIndex == index) {
		if (!restart) {
			return;
		}
	}

	currentAnimationIndex = index;
	currentFrameIndex = 0;

	frame = animations.get(currentAnimationIndex).frames.get(currentFrameIndex);
	setFps(animations.get(currentAnimationIndex).fps);

	flipH = animations.get(currentAnimationIndex).flipH;
	flipV = animations.get(currentAnimationIndex).flipV;

	loop = animations.get(currentAnimationIndex).loop;
	animationTimer.start();
}


void AnimatedSprite::setFps(int fps) {
	this->fps = fps;
	animationTimer.setLength(1.0 / ((float)fps * speedScale));
}

int AnimatedSprite::getFps() {
	return this->fps;
}

void AnimatedSprite::setSpeedScale(float speedScale) {
	if (speedScale == this->speedScale) {
		return;
	}

	if (speedScale <= 0) {
		speedScale = 0.1;
	}
	this->speedScale = speedScale;
	setFps(getFps());
}

float AnimatedSprite::getSpeedScale() {
	return this->speedScale;
}



void AnimatedSprite::animationTimerTimeout() {
	currentFrameIndex = (currentFrameIndex + 1) % animations.get(currentAnimationIndex).frames.getSize();
	frame = animations.get(currentAnimationIndex).frames.get(currentFrameIndex);


	if (!loop) {
		if (currentFrameIndex == animations.get(currentAnimationIndex).frames.getSize() - 1) {
			currentAnimationIndex = -1;
			animationFinished.emit();
			return;
		}
	}

	animationTimer.start();
}

int AnimatedSprite::findAnimationIndex(std::string name) {
	for (int i = 0; i < animations.getSize(); i++) {
		if (animations.get(i).name == name) {
			return i;
		}
	}
	return -1;
}

AnimatedSprite::Animation* AnimatedSprite::getAnimation(std::string name) {
	int index = findAnimationIndex(name);
	if (index == -1) {
		return nullptr;
	}
	return &animations.get(index);
}