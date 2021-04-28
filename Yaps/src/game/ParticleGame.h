#include "../core/System.h"
#include "../render/Model.h"
#include "Sprite.h"
#include "ParticleData.h"
#include "ParticleSimulator.h"
#include <vector>

class ParticleGame : public System {
	public:
		ParticleGame();
		int getRenderArr(std::queue<Model>& arr);
	private:
		Model display;
		void ParticleGame::scaleModel(Model& in, TransMatrix& scale);
		void bindSimData(ParticleSimulator sim);
		float zoom = 1;

		rect size;
		ParticleSimulator sim;
};
//No objects contained by mazeGame can use mouse positions