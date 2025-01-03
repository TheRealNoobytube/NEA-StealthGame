#pragma once
#include "Source/Nodes/Node.h"

class TimerNode : public Node {
public:
	TimerNode(std::string name = "TimerNode");
	
	void ready() override;
	void update(float delta) override;

	void start(float time = -1);
	void stop();
	void pause();


	void setCurrentTime(float time);
	float getCurrentTime();

	void setLength(float length);
	float getLength();


private:
	float currentTime = 0;
	float length = 10;

	bool paused = false;
	bool running = false;
	bool loop = false;



};
