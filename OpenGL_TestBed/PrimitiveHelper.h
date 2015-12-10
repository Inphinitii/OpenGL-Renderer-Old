#pragma once

#include "glew.h"
#include "MeshData.h"

#ifndef PRIMITIVE_HELPER_H
#define PRIMITIVE_HELPER_H

class PrimitiveHelper
{
public:
	static PrimitiveHelper* GetInstance();
	vector<Vertex> Cube();
	vector<Vertex> Quad();


private:
	static PrimitiveHelper* m_pHelperInstance;
	PrimitiveHelper(){}
	~PrimitiveHelper(){}

};

#endif