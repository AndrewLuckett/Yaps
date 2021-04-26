#include "../core/System.h"
#include "ParticleData.h"
#include <vector>

class ParticleSimulator : public System {
	public:
		ParticleSimulator(std::vector<ParticleData>& data, uint& width, uint& height);
		int update(timesys::system_clock::duration deltaTime);
};