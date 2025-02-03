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
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>

//Include GLM  
#include "Observer.h"
#include "ShaderLoader.h"

class Camera;

enum class ShaderType {
	PHONG,
	LAMBERT,
	CONSTANT,
	CLASSIC
};

class Shader : public Observer, public ShaderLoader
{
	public:
		Shader(ShaderType shaderType, const char* vertex_shader, const char* fragment_shader);
		void useProgram();	
		void passUniformLocation(glm::mat4 matrix, const char* name);
		void passUniformLocation(glm::vec3 vector, const char* name);
		void passUniformLocation(float value, const char* name);
		void update(void* object, ChangeType change);
		void unsetShader();
		ShaderType getShaderType();
	protected:
		ShaderType shaderType;
};

class ShaderPhong : public Shader {
	public:
		ShaderPhong(const char* vertex_shader, const char* fragment_shader)
			: Shader(ShaderType::PHONG, vertex_shader, fragment_shader) {}
};

class ShaderLambert : public Shader {
	public:
		ShaderLambert(const char* vertex_shader, const char* fragment_shader)
			: Shader(ShaderType::LAMBERT, vertex_shader, fragment_shader) {}
};

class ShaderClassic : public Shader {
public:
	ShaderClassic(const char* vertex_shader, const char* fragment_shader)
		: Shader(ShaderType::CLASSIC, vertex_shader, fragment_shader) {}
};

class ShaderConstant : public Shader {
public:
	ShaderConstant(const char* vertex_shader, const char* fragment_shader)
		: Shader(ShaderType::CONSTANT, vertex_shader, fragment_shader) {}
};