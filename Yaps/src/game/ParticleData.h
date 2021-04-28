#pragma once
#include "../global/Shorts.h"

typedef struct ParticleData { //Image data
	uchar red;
	uchar green;
	uchar blue;
	uchar velocity; //Pixels per frame

	//uuid of particle type based off colour
	//position from location in vector
	//velocity for velocity calc (ignored by shader... for now)

	ParticleData(uint hex) {
		red = (hex >> 16) & 0xFF;
		green = (hex >> 8) & 0xFF;
		blue = hex & 0xFF;
		velocity = 0;
	}

} ParticleData;
