#include "TimerNode.h"



TimerNode::TimerNode(std::string name) : Node(name) {

}

void TimerNode::ready() {
	__super::ready();
}

void TimerNode::update(float delta) {
	__super::update(delta);

	if (running && !paused) {
		currentTime += delta; //this is how the timer progresses

		if (length > 0) {
			if (getCurrentTime() > length) {
				setCurrentTime(length);

				//if loop is true, keep removing length until the timer is under the value of length
				//this is done as the program mightve been unfocused and any previous timeouts may not have been emitted
				if (loop) {
					do {
						start(getCurrentTime() - length);
						timeout.emit();
					} while (getCurrentTime() > length);
				}
				else {
					stop();
					timeout.emit();
				}

			}
		}
	}
}

void TimerNode::start(float time) {
	running = true;
	setCurrentTime(time);
}

void TimerNode::stop() {
	running = false;
}

void TimerNode::pause(bool pause) {
	paused = pause;
	if (paused) {
		stop();
	}
}

void TimerNode::setCurrentTime(float time) {
	if (time > 0) {
		this->currentTime = time ;
	}
	else {
		this->currentTime = 0;
	}
}

float TimerNode::getCurrentTime() {
	return this->currentTime;
}


void TimerNode::setLength(float length) {
	if (length > 0) {
		this->length = length;
	}
	else {
		this->length = 0.1;
	}
}

float TimerNode::getLength() {
	return this->length;
}

bool TimerNode::isRunning() {
	return running;
}