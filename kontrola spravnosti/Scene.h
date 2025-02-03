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
#include "vector"
#include "DrawableObject.h"
class Scene
{
	public:
		Scene();
		void addObject(DrawableObject* o);
		std::vector<DrawableObject*> objects;
};

