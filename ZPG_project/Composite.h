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
public:
	void add(Transformation* t);
	std::vector <Transformation*> children;
	glm::mat4 traverse();
	
};

