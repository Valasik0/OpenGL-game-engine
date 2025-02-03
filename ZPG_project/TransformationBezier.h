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
class TransformationBezier : public Transformation
{
	float t = 0.5f;
	float delta = 0.001;
	glm::mat4 A = glm::mat4(
		glm::vec4(-1.0, 3.0, -3.0, 1.0),
		glm::vec4(3.0, -6.0, 3.0, 0),
		glm::vec4(-3.0, 3.0, 0, 0),
		glm::vec4(1, 0, 0, 0));

	glm::mat4x3 B;

public:
	TransformationBezier(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
	glm::mat4 traverse();
};


