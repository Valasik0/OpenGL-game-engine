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
#include "vector"
#include "Shader.h"
#include "Composite.h"

class Model
{
	public:
		Model(const float points[], GLint size, int verticesCount, Shader* shader);
		void initModel();
		void bindArray();
		int getVerticesCount();
	private:
		GLuint VAO;
		GLuint VBO;
		GLint vertexSize;
		Shader* shader;
		int verticesCount;
		const float* points;
};

