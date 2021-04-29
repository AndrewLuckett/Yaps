#include "ParticleSimulator.h"
#include "ParticleTypes.h"

ParticleSimulator::ParticleSimulator() {}

ParticleSimulator::ParticleSimulator(int& width, int& height) {
	data = std::vector<ParticleData>();
	for (int i = 0; i < width * height; i++) data.push_back(ParticleData(0x000000));
	this->width = width;
	this->height = height;

	debugPrint("ParticleProperties: " << sizeof(ParticleProperties));
	debugPrint("ParticleData: " << sizeof(ParticleData));
	debugPrint("ParticleTypes: " << sizeof(ParticleTypes));
	debugPrint("Data: " << data.capacity());
	debugPrint("Data Bytes: " << data.capacity() * sizeof(ParticleData));

	for (int x = 0; x < width; x++) {
		for (int y = height - 1; y >= 100; y--) {
			*getParticle(x, y) = ParticleData((uint)ParticleNames::Water);
		}
	}
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

//int framer = -1;
void ParticleSimulator::updateParticles() {
	//if (framer < 0) {
	//	framer = height - 1;
	//}
	data[64] = ParticleData((uint)ParticleNames::Sand);
	//data[65] = ParticleData((uint)ParticleNames::Sand);
	//data[32] = ParticleData((uint)ParticleNames::Water);


	// Update full screen
	for (int x = 0; x < width; x++) {
		for (int y = height - 1; y >= 0; y--) {
			updateParticle(x, y);
		}
	}
	// Reset move status
	for (int x = 0; x < width; x++) {
		for (int y = height - 1; y >= 0; y--) {
			getParticle(x, y)->moved = false;
		}
	}
	//framer -= 1;
}

void ParticleSimulator::updateParticle(int x, int y) {
	ParticleProperties prop = getParticleProp(x, y);
	ParticleData part = *getParticle(x, y);
	//data[y * width + x].red = 100;
	//debugPrint(prop.name);
	if (prop.movable == 0 || part.moved == 1) return;

	if (prop.gravity >= 1 && y + 1 < height) {
		if (doGravity(x, y)) return;
	}
	if (prop.fluid == 1) {
		if (doFluid(x, y)) return;
	}
	if (prop.gravity >= 1 && y + 1 < height) {
		if (doSink(x, y)) return;
	}
	//if(prop.boyand == 0){
}

bool ParticleSimulator::doGravity(int x, int y) {
	ParticleProperties dl = getParticleProp(x, y + 1);
	if (dl.solid == 0) {
		swapParticles(x, y, x, y + 1);
		getParticle(x, y + 1)->moved = true;
		return true;
	}
	if (x > 0) {
		dl = getParticleProp(x - 1, y + 1);
		if (dl.solid == 0) {
			swapParticles(x, y, x - 1, y + 1);
			getParticle(x - 1, y + 1)->moved = true;
			return true;
		}
	}
	if (x + 1 < width) {
		dl = getParticleProp(x + 1, y + 1);
		if (dl.solid == 0) {
			swapParticles(x, y, x + 1, y + 1);
			getParticle(x + 1, y + 1)->moved = true;
			return true;
		}
	}
	return false;
}

bool ParticleSimulator::doFluid(int x, int y) {
	if (x > 0) {
		ParticleProperties dl = getParticleProp(x - 1, y);
		if (dl.solid == 0) {
			swapParticles(x, y, x - 1, y);
			getParticle(x - 1, y)->moved = true;
			return true;
		}
	}
	if (x + 1 < width) {
		ParticleProperties dl = getParticleProp(x + 1, y);
		if (dl.solid == 0) {
			swapParticles(x, y, x + 1, y);
			getParticle(x + 1, y)->moved = true;
			return true;
		}
	}
	return false;
}

bool ParticleSimulator::doSink(int x, int y) {
	ParticleProperties below = getParticleProp(x, y + 1);
	ParticleData part = *getParticle(x, y + 1);
	if (below.fluid == 1){// && part.moved == 0) {
		swapParticles(x, y, x, y + 1);
		getParticle(x, y + 1)->moved = true;
		getParticle(x, y)->moved = true;
		return true;
	}
	return false;
}

ParticleProperties ParticleSimulator::getParticleProp(int x, int y) {
	ParticleData particle = data[y * width + x];
	uint particleColour = (particle.red << 16) + (particle.green << 8) + particle.blue;

	return ParticleTypes[particleColour];
}

ParticleData* ParticleSimulator::getParticle(int x, int y) {
	return &data[y * width + x];
}

void ParticleSimulator::swapParticles(int x1, int y1, int x2, int y2) {
	ParticleData temp = data[y1 * width + x1];
	data[y1 * width + x1] = data[y2 * width + x2];
	data[y2 * width + x2] = temp;
}
