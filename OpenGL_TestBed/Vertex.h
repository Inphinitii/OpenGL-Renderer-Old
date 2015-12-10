#pragma once

//If using GLM, else comment out
#include "glm.hpp"

#ifdef GLM_INCLUDED
bool glMath = true;
#endif

//Custom Vec3, etc..
//...

#ifndef VERTEX_H
#define VERTEX_H

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec3 TextureCoords;
};

#endif