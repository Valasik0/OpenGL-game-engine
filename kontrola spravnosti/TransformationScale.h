//***************************************************************************
//
// Project for subject ZPG
//
// Václav Vyrobík, VYR0020
//
// 2023
// 
//***************************************************************************
#pragma once
#include "Transformation.h"
class TransformationScale: public Transformation
{
	glm::vec3 values;

	public:
		TransformationScale(glm::vec3 values);
		glm::mat4 traverse();
};

