#pragma once
#include "Source/Nodes/Node2D/Node2D.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Source/Application/Texture.h"

class Sprite : public Node2D {
private:
	Texture* texture;

public:
	Sprite(Texture* texture, std::string name = "Sprite");
	void ready() override;
	void update(float delta) override;
	
};