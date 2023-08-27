#pragma once
#include "Actor.h"
#include <map>
#include <glm/glm.hpp>
#include "../include/imgui/imgui.h"
#include "Basicshape/ibox.h"

class Skybox : public Actor {
public:
	//friend class VolumetricClouds;
	Skybox();
	~Skybox();

	void draw(float time) override;
	//void update() {};

	void setGUI();
	void Flipdraw() ;

private:
	ibox* geometry;
	unsigned int textureid[5];
	float scale, height;

};

