#pragma once
#include "Source/Nodes/Node2D/Node2D.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Source/Application/Texture.h"

class Sprite : public Node2D {
private:
	Texture* texture;
	int vFrames = 1;
	int hFrames = 1;

public:
	bool flipH = false;
	bool flipV = false;
	int frame = 0;

	Sprite(std::string filepath = "", std::string name = "Sprite");
	Sprite(Texture* texture, std::string name = "Sprite");
	~Sprite();

	void ready() override;
	void update(float delta) override;
	void setTexture(Texture* texture);
	void setTexture(std::string filepath);

	//void setFrame(int frame);
	//int getFrame();

	void setVFrames(int vFrames);
	void setHFrames(int hFrames);
	int getVFrames();
	int getHFrames();
};