#pragma once

#include <string>
#include "Camera.h"
#include "SceneInfo.h"
#include "../include/stb_image.h"
#include "../Engine/Shader.h"


class Actor {
public:
	unsigned int loadtexture(const std::string& directory, bool gamma) ;
	unsigned int loadSkytexture(const std::string& directory, bool gamma) ;

	virtual void draw(float time) {};
	virtual void update() {};
	Shader * _shader;
	SceneInfo* _sceneIF;

};