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
#include "ChangeType.h"
class Observer
{
public:
	virtual void update(void* object, ChangeType change) = 0;
};

