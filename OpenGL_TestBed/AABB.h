#pragma once
#include "glm.hpp"

#ifndef AABB_H
#define AABB_H

//Currently only in 2D
struct BoundingBox
{
	glm::vec2	topRight,
				topLeft,
				bottomRight,
				bottomLeft;
};

class AABB
{
public:
	AABB(glm::vec2 _min, glm::vec2 _max);
	~AABB();

	BoundingBox Bounds() { return m_boundingBox; }

private:
	glm::vec2	m_maxValue; //Top right
	glm::vec2	m_minValue; //Bottom left
	BoundingBox m_boundingBox;

	void GenerateAABB();
};


#endif