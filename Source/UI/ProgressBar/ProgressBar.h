#pragma once
#include "Source/Nodes/Node2D/Node2D.h"
#include "Source/UI/Button/Button.h"

class ProgressBar : public Node2D {

public:
	Texture background = Texture();
	Texture progress = Texture();

	Vector2D size = Vector2D(50, 10);

	float min = 0;
	float max = 100;
	float value = 0;

public:
	ProgressBar(std::string name = "ProgressBar");

	bool visible = true;

	void ready() override;
	void update(float delta) override;

	virtual void setValue(float value);
	float getValue();
	void setMin(float min);
	void setMax(float max);

	void setSize(Vector2D size);
	Vector2D getSize();
};