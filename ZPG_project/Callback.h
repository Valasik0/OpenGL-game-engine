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
#include <GL/glew.h>
#include <GLFW/glfw3.h>  

#include <stdlib.h>
#include <stdio.h>
#include "Camera.h"
#include "Scene.h"

class Callback
{
public:
	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void cursor_callback(GLFWwindow* window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);
	static void initCallbacks(GLFWwindow* window, Camera* camera, Scene* scene);
	static Callback& getInstance();

private:
	Callback();
	static Camera* camera;
	static Scene* scene;
	Callback(const Callback&) = delete;
	Callback& operator=(const Callback&) = delete;
};