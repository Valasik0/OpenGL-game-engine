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
#include "Subject.h"

class Light : public Subject
{
	public:
		Light(glm::vec3 lightPosition, glm::vec3 lightColor);
		void update(void* object);
		void updatePosition(glm::vec3 newPosition);
		void updateColor(glm::vec3 newPosition);
		glm::vec3 getLightPosition();
		glm::vec3 getLightColor();
	private:
		glm::vec3 lightPosition;
		glm::vec3 lightColor;
};

