#include "Terrain.h"
#include <GLFW/glfw3.h>
#include "../include/imgui/imgui.h"

Terrain::Terrain()
{	
	int res = 20;
	this->_shader = new Shader("shader/terrain.vert.glsl",
								"shader/terrain.tcs.glsl",
								"shader/terrain.tes.glsl",
								"shader/terrain.frag.glsl");

	this->geometry = new Plane(res);
	this->height = 15.5;

	this->frequency = 1;
	this->offset = 0;
	this->amplitude = 1;
	this->octave = 4;

	this->Rockscale = 10;
	this->Grassscale = 10;
	this->trans_gs = 1;
	this->trans_sr = 1;
	this->grassRange = 0.3;
	this->slopeRange = 0.6;
	this->rockRange = 0.8;

	std::string pathlist[6] = { "resources/forrest_ground_01_diff_1k.jpg",
								"resources/coast_sand_rocks_02_diff_1k.jpg" ,
								"resources/aerial_rocks_02_diff_1k.jpg" ,
								"resources/forrest_ground_01_ao_1k.jpg" ,
								"resources/coast_sand_rocks_02_ao_1k.jpg" ,
								"resources/forrest_ground_01_ao_1k.jpg"
	};

	for (int i = 0; i < 6; ++i) {
		//texture
		this->textureid[i] = loadtexture(pathlist[i], 1);
	}

	

}

void Terrain::Flipdraw() {

	this->_shader->use();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0, height - 29.552, 0));
	model = glm::scale(model, glm::vec3(1, -1, 1));
	this->_shader->setMat4("model", model);

	this->_shader->setFloat("frequency", frequency);
	this->_shader->setFloat("offset", offset);
	this->_shader->setFloat("amplitude", amplitude);
	this->_shader->setInt("octave", octave);

	this->_shader->setFloat("grassRange", grassRange);
	this->_shader->setFloat("slopeRange", slopeRange);
	this->_shader->setFloat("rockRange", rockRange);
	this->_shader->setFloat("Grassscale", Grassscale);
	this->_shader->setFloat("Rockscale", Rockscale);
	this->_shader->setFloat("trans_gs", trans_gs);
	this->_shader->setFloat("trans_sr", trans_sr);

	this->_shader->setTex2D("grass_map", textureid[0], 0);
	this->_shader->setTex2D("slope_map", textureid[1], 1);
	this->_shader->setTex2D("rock_map", textureid[2], 2);
	this->_shader->setTex2D("grass_aomap", textureid[3], 3);
	this->_shader->setTex2D("slope_aomap", textureid[4], 4);
	this->_shader->setTex2D("rock_aomap", textureid[5], 5);

	this->geometry->renderPatch();
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
}

void Terrain::draw(float time) {

	
	this->_shader->use();

	glm::mat4 view = this->_sceneIF->cam->GetViewMatrix();
	this->_shader->setMat4("projection", this->_sceneIF->projMatrix);
	this->_shader->setMat4("view", view);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0, height, 0));
	this->_shader->setMat4("model", model);

	this->_shader->setFloat("frequency", frequency);
	this->_shader->setFloat("offset", offset);
	this->_shader->setFloat("amplitude", amplitude);
	this->_shader->setInt("octave", octave);

	this->_shader->setFloat("grassRange", grassRange);
	this->_shader->setFloat("slopeRange", slopeRange);
	this->_shader->setFloat("rockRange", rockRange);
	this->_shader->setFloat("Grassscale", Grassscale);
	this->_shader->setFloat("Rockscale", Rockscale);
	this->_shader->setFloat("trans_gs", trans_gs);
	this->_shader->setFloat("trans_sr", trans_sr);

	this->_shader->setTex2D("grass_map", textureid[0], 0);
	this->_shader->setTex2D("slope_map", textureid[1], 1);
	this->_shader->setTex2D("rock_map", textureid[2], 2);
	this->_shader->setTex2D("grass_aomap", textureid[3], 3);
	this->_shader->setTex2D("slope_aomap", textureid[4], 4);
	this->_shader->setTex2D("rock_aomap", textureid[5], 5);


	this->geometry->renderPatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);

}

void Terrain::setGui()
{
	ImGui::Begin("Terrain controls: ");
	//ImGui::TextColored(ImVec4(1, 1, 0, 1), "Terrain Controls");
	////ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
	////ImGui::Checkbox("Clouds PostProc + God Rays", this->getPostProcPointer());
	//ImGui::SliderInt("Octaves", &octaves, 1, 20);
	ImGui::Text("noise control");
	//ImGui::SliderFloat("Height", &height, 0.0f, 100.0f);
	ImGui::SliderFloat("Frequency", &frequency, 0.1f,10.0f );
	ImGui::SliderFloat("offset", &offset, 0.0f, 10.0f);
	ImGui::SliderFloat("amplitude", &amplitude, 0.0f, 10.0f);
	ImGui::SliderInt("octave", &octave, 0, 20);

	ImGui::Text("map control");
	ImGui::SliderFloat("Grassscale", &Grassscale, 1.0f, 30.f);
	ImGui::SliderFloat("Rockscale", &Rockscale, 1.0f, 30.f);
	ImGui::SliderFloat("trans_gs", &trans_gs, 0.1f, 5.f);
	ImGui::SliderFloat("trans_sr", &trans_sr, 0.1f, 5.f);
	ImGui::SliderFloat("grassRange", &grassRange, 0.0f, 1.0f);
	ImGui::SliderFloat("slopeRange", &slopeRange, 0.0f, 1.0f);
	ImGui::SliderFloat("rockRange", &rockRange, 0.0f, 1.0f);
	////glm::vec3 * cloudBottomColor = this->getCloudColorBottomPtr();
	////ImGui::ColorEdit3("Cloud color", (float*)cloudBottomColor); // Edit 3 floats representing a color

	////ImGui::TextColored(ImVec4(1, 1, 0, 1), "Sky controls");
	//ImGui::ColorEdit3("Rock color", (float*)&rockColor[0]); // Edit 3 floats representing a color
	//ImGui::ColorEdit3("Sky bottom color", (float*)this->getSkyBottomColorPtr()); // Edit 3 floats representing a color
	ImGui::End();
}




Terrain::~Terrain()
{
	delete this->_shader;
	delete this->geometry;
}

