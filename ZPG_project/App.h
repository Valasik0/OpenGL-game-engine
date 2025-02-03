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
#include "Callback.h"
#include "Scene.h"

class App
{
	private:
		Callback* callback;
		Scene* scene;
		void initWindow();
		void printInfo();
		void chooseScene();
		int choice;
		
	public:
		App();
		void runApp();
		GLFWwindow* window;
};
