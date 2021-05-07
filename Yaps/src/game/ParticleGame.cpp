#include "ParticleGame.h"
#include "Engine/render/Texture.h"
#include "Engine/render/Vao.h"
#include "Engine/render/Window.h"
#include "Engine/core/input.h"
#include "Engine/render/ShaderGen.h"
#include "Engine/render/Renderer.h"

ParticleGame::ParticleGame() {
	size = { 256,256 };

	sim = ParticleSimulator(size.x, size.y);
	addSubSystem(&sim);

	display = getGenericModel();
	glGenTextures(1, &display.textureId);

	uint prog = GenerateProgram("res/shaders/core.vert", "res/shaders/particle.frag");
	display.programId = prog;

	glBindTexture(GL_TEXTURE_2D, display.textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	bindSimData(sim);

	//display.textureId = loadTexture("res/textures/notes.png", GL_NEAREST);
}

int ParticleGame::getRenderArr(std::queue<Model>& arr) {
	rect windowSize = window::getWindowSize();
	float aspect = windowSize.x * 1.0f / windowSize.y;
	TransMatrix scale;
	scale.top = { zoom, 0.0f, 0.0f };
	scale.mid = { 0.0f, zoom, 0.0f };

	if (windowSize.y < windowSize.x) {
		scale.top.x /= aspect;
	} else {
		scale.mid.y *= aspect;
	}
	renderer::loadGlobalTransform(display.programId, scale);

	bindSimData(sim);

	arr.push(display);
	return 0;
}

void ParticleGame::scaleModel(Model& in, TransMatrix& scale) {
	in.transform = matrixMult(scale, in.transform);
}

void ParticleGame::bindSimData(ParticleSimulator sim) {
	glBindTexture(GL_TEXTURE_2D, display.textureId);
	ParticleData* datap = 0;
	size = sim.getData(datap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, datap);
	glBindTexture(GL_TEXTURE_2D, 0);
}
