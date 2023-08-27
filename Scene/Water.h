#pragma once
#include "../Engine/Shader.h"
#include "Basicshape/Plane.h"
#include "Actor.h"
#include <glm/glm.hpp>
#include "../include/imgui/imgui.h"

class Water : public Actor
{
public:
	Water(float h = 0.729, float s = 1000);
	~Water();

	void draw(float time) override;
	void setGUI();

private:

	Plane* geometry;
	float scale, height;
	float freq, offset, speed;
	unsigned int textureid[5];

};
