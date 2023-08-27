#pragma once
#include <glm/glm.hpp>
//#include <model.h>
//#include "TessShader.h"
#include "Camera.h"
#include "Actor.h"
#include "Basicshape/Plane.h"

enum tPosition {
	C, N, S, E, W, SE, SW, NE, NW, totTiles
};

class Terrain : public Actor
{
public:

	Terrain();

	~Terrain();
	void draw(float time) override;
	void setGui();
	void Flipdraw();

private:

	Plane* geometry;
	float height;
	unsigned int textureid[6];

	//noise control
	float frequency;
	float offset;
	float amplitude;
	int octave;

	//texture control
	float Grassscale;
	float Rockscale;
	float trans_gs;
	float trans_sr;
	float grassRange;
	float slopeRange;
	float rockRange;

};

