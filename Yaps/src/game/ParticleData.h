#include "../global/Shorts.h"

typedef struct ParticleData {
	uchar red;
	uchar green;
	uchar blue;
	uchar velocity; //Pixels per frame

	//uuid of particle type based off colour
	//position from location in vector
	//velocity for velocity calc (ignored by shader... for now)

} ParticleData;
