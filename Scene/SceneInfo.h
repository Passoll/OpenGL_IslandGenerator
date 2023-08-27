#pragma once

#include "Camera.h"
#include <glm/glm.hpp>

struct SceneInfo {

	glm::vec3 lightPos, lightColor, lightDir, fogColor, seed;
	glm::mat4 projMatrix;
	Camera* cam;
	bool wireframe = false;
};