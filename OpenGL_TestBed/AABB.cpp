#include "AABB.h"


AABB::AABB(glm::vec2 _min, glm::vec2 _max)
{
	m_minValue = _min;
	m_maxValue = _max;
	GenerateAABB();
}


AABB::~AABB()
{
}

void AABB::GenerateAABB()
{
	//NOT FOOL PROOF IF THE TWO POINTS SUPPLIED AREN'T EXACTLY RIGHT
	m_boundingBox.bottomRight	= glm::vec2(m_maxValue.x, m_minValue.y);
	m_boundingBox.bottomLeft	= glm::vec2(m_minValue.x, m_minValue.y);

	m_boundingBox.topRight		= glm::vec2(m_maxValue.x, m_maxValue.y);
	m_boundingBox.topLeft		= glm::vec2(m_minValue.x, m_maxValue.y);
}
