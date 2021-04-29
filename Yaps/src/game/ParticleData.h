#pragma once
#include "../global/Shorts.h"

typedef struct ParticleProperties {
	uint gravity : 2; // Will gravity cause it to move? (First for better packing)
	//0 = No gravity ever, 1 = Normal gravity always
	//2 = Reverse gravity always, 3 = Uses gravity once moving
	bool solid : 1; // Will it block moving particles
	bool movable : 1; // Can it move?
	bool fluid : 1; // Will it disperse laterally?
	bool flammable : 1; // Can it burn?
	bool boilable : 1; // Can it produce steam?
	bool hot : 1; // Will it burn its surroundings?
	bool decay : 1; // Will it slowly vanish when stationary

	string name;
} ParticleProperties;

typedef struct ParticleData { //Image data
	uchar red;
	uchar green;
	uchar blue;
	//uchar velocity : 3; //Pixels per frame
	bool moved;
	//uuid of particle type based off colour
	//position from location in vector
	//velocity for velocity calc (ignored by shader... for now)

	ParticleData(uint hex) {
		red = (hex >> 16) & 0xFF;
		green = (hex >> 8) & 0xFF;
		blue = hex & 0xFF;
		//velocity = 0;
		moved = false;
	}

} ParticleData;
