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
class TransformationLine : public Transformation
{
	float t = 0.5f;
	float delta = 0.001;

	glm::vec3 A;
	glm::vec3 B;

public:
	TransformationLine(glm::vec3 p0, glm::vec3 p1);
	glm::mat4 traverse();
};

