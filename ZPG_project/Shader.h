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
#include "vector"

#define COLOR_VERTEX "./Shaders/Vertex/vertex.vert"
#define LIGHT_VERTEX "./Shaders/Vertex/light.vert"
#define TEXTURE_VERTEX "./Shaders/Vertex/texture.vert"
#define SKYBOX_VERTEX "./Shaders/Vertex/skybox.vert"

#define PHONG_ "./Shaders/Fragment/phong.frag"
#define BLINN_ "./Shaders/Fragment/blinn.frag"
#define PHONG_WRONG "./Shaders/Fragment/phong_wrong.frag"
#define LAMBERT_ "./Shaders/Fragment/lambert.frag"
#define CONSTANT_ "./Shaders/Fragment/constant.frag"
#define COLOR_FRAGMENT "./Shaders/Fragment/fragment.frag"
#define TEXTURE_ "./Shaders/Fragment/texture.frag"
#define SKYBOX "./Shaders/Fragment/skybox.frag"

class Camera;

enum class ShaderType {
	PHONG,
	LAMBERT,
	BLINN,
	CONSTANT,
	CLASSIC,
	TEXTURE,
	CUBEMAP
};

class Shader : public Observer, public ShaderLoader
{
	public:
		Shader(ShaderType shaderType, const char* vertex_shader, const char* fragment_shader);
		void useProgram();	
		void passUniformLocation(glm::mat4 matrix, const char* name);
		void passUniformLocation(glm::vec3 vector, const char* name);
		void passUniformLocation(float value, const char* name);
		void passUniformLocation(int value, const char* name);	
		void passUniformLocation(GLuint value, const char* name);
		void update(void* object, ChangeType change);
		void unsetShader();
		void loadShaders();
		ShaderType getShaderType();
	protected:
		ShaderType shaderType;
	private:
		int flashlightPosition;
		
};

class ShaderPhong : public Shader {
	public:
		ShaderPhong(const char* vertex_shader, const char* fragment_shader)
			: Shader(ShaderType::PHONG, vertex_shader, fragment_shader) {}
};

class ShaderBlinn : public Shader {
public:
	ShaderBlinn(const char* vertex_shader, const char* fragment_shader)
		: Shader(ShaderType::BLINN, vertex_shader, fragment_shader) {}
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

class ShaderTexture : public Shader {
public:
	ShaderTexture(const char* vertex_shader, const char* fragment_shader)
		: Shader(ShaderType::TEXTURE, vertex_shader, fragment_shader) {}
};

class ShaderCubemap : public Shader {
public:
	ShaderCubemap(const char* vertex_shader, const char* fragment_shader)
		: Shader(ShaderType::CUBEMAP, vertex_shader, fragment_shader) {}
};