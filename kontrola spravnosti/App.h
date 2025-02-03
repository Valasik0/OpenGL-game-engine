#pragma once
#include "Callback.h"
#include "Scene.h"
//***************************************************************************
//
// Project for subject ZPG
//
// V�clav Vyrob�k, VYR0020
//
// 2023
// 
//***************************************************************************
class App
{
	private:
		Callback* callback;
		void initWindow();
		void printInfo();
		void chooseScene();
		int choice;
	public:
		App();
		void runApp();
		GLFWwindow* window;
};
