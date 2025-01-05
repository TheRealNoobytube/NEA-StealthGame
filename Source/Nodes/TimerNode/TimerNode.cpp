#include "TimerNode.h"



TimerNode::TimerNode(std::string name) : Node(name) {

}

void TimerNode::ready() {

}

void TimerNode::update(float delta) {
	if (running) {
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

	if (!paused) {
		setCurrentTime(0);
	}
	else if (time != -1) {
		setCurrentTime(time);
	}
	else {
		paused = false;
	}
	
}

void TimerNode::stop() {
	running = false;
}

void TimerNode::pause() {
	paused = true;
	stop();
}

void TimerNode::setCurrentTime(float time) {
	if (time > 0) {
		this->currentTime = time * 1000000000;
	}
	else {
		this->currentTime = 0;
	}
}

float TimerNode::getCurrentTime() {
	return this->currentTime / 1000000000;
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