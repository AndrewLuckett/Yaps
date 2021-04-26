#include "ParticleGame.h"
#include "../render/Texture.h"
#include "../render/Vao.h"
#include "../render/Window.h"
#include "../core/input.h"
#include <iostream>

uint count = 0;


ParticleGame::ParticleGame() {
	width = 256;
	height = 256;

	display = getGenericModel();
	glGenTextures(1, &display.textureId);

	for (int i = 0; i < width * height; i++) data.push_back({ 0,0,0,0 });

	glBindTexture(GL_TEXTURE_2D, display.textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data);
	glBindTexture(GL_TEXTURE_2D, 0);

	//display.textureId = loadTexture("res/textures/notes.png", GL_NEAREST);
}

int ParticleGame::update(timesys::system_clock::duration deltaTime) {
	System::update(deltaTime);
	count++;
	data[count] = { 0xff,0x00,0xff,0xff };
	if (count >= width * height) {
		count = 0;
	}
	glBindTexture(GL_TEXTURE_2D, display.textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data[0]);
	glBindTexture(GL_TEXTURE_2D, 0);
	return 0;
}

int ParticleGame::getRenderArr(std::queue<Model> &arr) {
	rect windowSize = window::getWindowSize();
	float aspect = windowSize.x * 1.0f / windowSize.y;
	TransMatrix scale;
	scale.top = { zoom, 0.0f, 0.0f };
	scale.mid = { 0.0f, zoom * aspect , 0.0f };

	if (windowSize.y < windowSize.x) {
		scale.top = { zoom / aspect, 0.0f, 0.0f };
		scale.mid = { 0.0f, zoom, 0.0f };
	}

	std::queue<Model> sub;
	System::getRenderArr(sub);
	sub.push(display);

	while (!sub.empty()) {
		arr.push(scaleModel(sub.front(), scale));
		sub.pop();
	}
	return 0;
}

Model ParticleGame::scaleModel(Model in, TransMatrix scale) {
	in.transform = matrixMult(scale, in.transform);
	return in;
}