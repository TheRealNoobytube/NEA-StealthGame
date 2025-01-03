#include "AnimationPlayer.h"

AnimationPlayer::AnimationPlayer(std::string name) : Node(name) {
	addChild(&animationTimer);
}


void AnimationPlayer::ready() {
	animationTimer.setLength(20);
	animationTimer.start();
}


void AnimationPlayer::update(float delta) {

}



void AnimationPlayer::addAnimation(Animation* animation) {
	this->animations.add(animation);
	this->keys.add(animation->name);
}

Animation* AnimationPlayer::getAnimation(std::string name) {
	int index = keys.find(name);
	return animations.get(index);
}

void AnimationPlayer::removeAnimation(std::string name) {
	int index = keys.find(name);

	animations.remove(index);
	keys.remove(index);
}

void AnimationPlayer::play(std::string name) {
	Animation* animation = getAnimation(name);
	//auto track = animation->getTrack(0);

	
}