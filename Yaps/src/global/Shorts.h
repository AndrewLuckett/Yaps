#pragma once
//Shorter versions of stuff

#include <string>

#define Default(t, s) t s = 0;
// Create and init a var

#ifdef _DEBUG
	#include <iostream>
	#define debugCout(v) std::cout << v << std::endl;
#endif

#ifndef debugCout
	#define debugCout(v)
#endif


typedef unsigned int uint;
typedef unsigned char uchar;
typedef std::string string;

typedef struct vec2 {
	float x;
	float y;
} vec2;

typedef struct vec3 {
	float x;
	float y;
	float z;
} vec3;

typedef struct rect {
	int x;
	int y;
} rect;
