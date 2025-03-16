#pragma once

#include "Source/UI/Button/Button.h"
#include "Source/UI/ProgressBar/ProgressBar.h"

class Slider : public ProgressBar {
private:
	Button* sliderButton = new Button();
public:
	Slider(std::string name = "Slider");

	void ready() override;
	void update(float delta) override;

	void setValue(float value) override;
};