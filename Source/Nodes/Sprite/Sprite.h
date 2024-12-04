#pragma once
#include "../Node2D/Node2D.h"
#include "SDL.h"
#include "SDL_image.h"
#include "../../Application/Texture.h"

class Sprite : public Node2D {
private:
	Texture* texture;

public:
	Sprite(Texture* texture = nullptr);
	void ready() override;
	void update(float delta) override;
	
};