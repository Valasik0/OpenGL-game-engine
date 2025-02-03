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
#include "ChangeType.h"
class Observer
{
public:
	virtual void update(void* object, ChangeType change) = 0;
};

