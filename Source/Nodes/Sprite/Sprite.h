#pragma once
#include "../Node2D/Node2D.h"
#include "SDL.h"
#include "SDL_image.h"
#include "../../Application/Texture.h"

class Sprite : public Node2D {
private:
	Texture texture = Texture(nullptr, "");

public:
	Sprite(std::string texturePath);
	Sprite(Texture texture);
	Sprite();
	void ready() override;
	void update(float delta) override;
	
};