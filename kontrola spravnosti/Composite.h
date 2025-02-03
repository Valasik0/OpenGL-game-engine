//***************************************************************************
//
// Project for subject ZPG
//
// V�clav Vyrob�k, VYR0020
//
// 2023
// 
//***************************************************************************
#pragma once
#include "Transformation.h"
#include "vector"
class Composite: public Transformation
{
	std::vector <Transformation*> children;
	
public:
	void add(Transformation* t);

	glm::mat4 traverse();
	
};

