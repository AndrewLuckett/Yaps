#include "../core/System.h"
#include "../render/Model.h"
#include "Sprite.h"
#include "ParticleData.h"
#include <vector>

class ParticleGame : public System {
    public:
		ParticleGame();
	    int update(timesys::system_clock::duration deltaTime);
	    int getRenderArr(std::queue<Model> &arr);
    private:
		Model display;
		Model ParticleGame::scaleModel(Model in, TransMatrix scale);
		float zoom = 1;

		uint width, height;
		std::vector<ParticleData> data;
		//ParticleData data [256*256];
};
//No objects contained by mazeGame can use mouse positions