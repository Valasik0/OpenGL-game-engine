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
class TransformationTranslate : public Transformation
{
	glm::vec3 values;

	public:
		TransformationTranslate(glm::vec3 values);
		glm::mat4 traverse();
};

