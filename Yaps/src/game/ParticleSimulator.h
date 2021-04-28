#include "../core/System.h"
#include "ParticleData.h"
#include <vector>

class ParticleSimulator : public System {
	public:
		ParticleSimulator();
		ParticleSimulator(int& width, int& height);
		int update(timesys::system_clock::duration deltaTime);
		rect getData(ParticleData*& datap); // Returns raw array pointer to data
		float updateTime = 200; // ms
	private:
		void updateParticles();
		void updateParticle(int x, int y);
		std::vector<ParticleData> data;
		int width;
		int height;
		float timeUntilUpdate = 0;
};