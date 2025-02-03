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
#include <iostream>
#include <vector>
#include "TextureManager.h"

class Material
{
	private:
		float specular = 0.0f;
		glm::vec3 ambient = glm::vec3(0.0f);
		float diffuse = 0.0f;
		glm::vec3 objectColor = glm::vec3(0.0f);
		int uvMult;
		GLuint textureID = -1;
	public:
		Material(glm::vec3 objectColor,float specular,glm::vec3 ambient,float diffuse);
		Material(glm::vec3 objectColor, glm::vec3 ambient, float diffuse);
		Material(glm::vec3 objectColor);
		Material(std::string texturePath);
		Material(std::string texturePath, int uvMult);
		Material(std::vector<std::string> skybox);
		Material();
		float getSpecular();
		glm::vec3 getAmbient();
		glm::vec3 getObjectColor();
		float getDiffuse();
		GLuint getTextureID();
		int getUvMult();
		void highlight();
};

