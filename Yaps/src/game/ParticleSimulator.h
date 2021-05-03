#include "Engine/core/System.h"
#include "ParticleData.h"
#include <vector>

class ParticleSimulator : public System {
	public:
		ParticleSimulator();
		ParticleSimulator(int& width, int& height);
		int update(timesys::system_clock::duration deltaTime);
		rect getData(ParticleData*& datap); // Returns raw array pointer to data
		float updateTime = 0;// 33;// ms
	private:
		void updateParticles();
		void updateParticle(int x, int y);
		bool doGravity(int x, int y);
		bool doFluid(int x, int y);
		bool doSink(int x, int y);
		ParticleProperties getParticleProp(int x, int y);
		ParticleData* getParticle(int x, int y);
		void swapParticles(int x1, int y1, int x2, int y2);
		std::vector<ParticleData> data;
		int width;
		int height;
		float timeUntilUpdate = 0;
};