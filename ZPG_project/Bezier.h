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
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>
#include <algorithm> 

class Bezier
{
	public:
		Bezier(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
		glm::vec3 getBezierPoint();
		void updateParametr(float delta);
	private:
		float t = 0.5f;
		bool growing = true;
		glm::mat4 A = glm::mat4(
			glm::vec4(-1.0, 3.0, -3.0, 1.0),
			glm::vec4(3.0, -6.0, 3.0, 0),
			glm::vec4(-3.0, 3.0, 0, 0),
			glm::vec4(1, 0, 0, 0));

		glm::mat4x3 B;
	
};

