#include "ParticleSimulator.h"
#include "ParticleProperties.h"

ParticleSimulator::ParticleSimulator() {}

ParticleSimulator::ParticleSimulator(int& width, int& height) {
	data = std::vector<ParticleData>();
	for (int i = 0; i < width * height; i++) data.push_back(ParticleData(0x000000));
	this->width = width;
	this->height = height;
}

int ParticleSimulator::update(timesys::system_clock::duration deltaTime) {
	timeUntilUpdate -= (float)timesys::duration_cast<timesys::microseconds>(deltaTime).count() / 1000;
	if (timeUntilUpdate <= 0) {
		updateParticles();
		timeUntilUpdate = updateTime;
	}
	return 0;
}

rect ParticleSimulator::getData(ParticleData*& datap) {
	datap = &data[0];
	return { width, height };
}

void ParticleSimulator::updateParticles() {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			updateParticle(x, y);
		}
	}
}

void ParticleSimulator::updateParticle(int x, int y) {
	ParticleData particle = data[y * width + x];
	uint particleColour = (particle.red << 16) + (particle.green << 8) + particle.blue;
	data[y * width + x].red = 255;

	ParticleProperties prop = ParticleTypes[particleColour];
	//debugCout(prop.name);

}

