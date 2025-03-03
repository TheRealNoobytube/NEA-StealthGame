#pragma once
#include "Source/Nodes/Node2D/Node2D.h"
#include "Source/UI/Button/Button.h"

class Slider : public Node2D {
private:
	Texture sliderBackground;
	Texture sliderProgress;

	Button* sliderButton = new Button();

	Vector2D size = Vector2D(50, 10);

	float min = 0;
	float max = 100;
	float value = 0;

public:
	Slider(std::string name = "Slider");

	void ready() override;
	void update(float delta) override;

	void setValue(float value);
	float getValue();
	void setMin(float min);
	void setMax(float max);

	void setSize(Vector2D size);
	Vector2D getSize();
};