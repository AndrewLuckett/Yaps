#include "../global/Shorts.h"
#include <unordered_map>
#include "ParticleData.h"

enum class  ParticleNames {
	Air = 0x000000,
	Sand = 0xeecc99,
	Water = 0x0f0fff,
	Smoke = 0x404040,
	Steam = 0xa0a0a0
};

static std::unordered_map<uint, ParticleProperties> ParticleTypes = {
	{(uint)ParticleNames::Air, {0, 0, 0, 0, 0, 0, 0, 0, "Air"}},
	{(uint)ParticleNames::Sand, {2, 1, 1, 0, 0, 0, 0, 0, "Sand"}},
	{(uint)ParticleNames::Water, {2, 1, 1, 1, 0, 1, 0, 0, "Water"}},
	{(uint)ParticleNames::Smoke, {3, 0, 1, 1, 0, 0, 0, 1, "Smoke"}},
	{(uint)ParticleNames::Steam, {3, 0, 1, 1, 0, 0, 0, 1, "Steam"}}
};
