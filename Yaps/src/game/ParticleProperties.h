#include "../global/Shorts.h"
#include <unordered_map>

typedef struct ParticleProperties {
	std::string name;
	bool gravity;
	bool fluid;
} ParticleProperties;

std::unordered_map<uint, ParticleProperties> ParticleTypes = {
	{0x000000, {"Air", 0, 0}},
	{0xeecc99, {"Sand", 1, 0}},
	{0x0f0fff, {"Water", 1, 1}}
};