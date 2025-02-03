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

enum class LightType {
	DIRECTION = 0,
	POINT = 1,
	SPOT = 2,
	FLASHLIGHT = 3
};


class Light : public Subject
{
	public:
		Light(LightType lightType, glm::vec3 lightColor);
		virtual ~Light() {}
		void update(void* object);
		void updateColor(glm::vec3 color);
		glm::vec3 getLightColor();
		LightType getLightType();
		void toggleOnOff();
		int isLightOn();
		virtual float getConstantAtt() { return 0.0f; }
		virtual float getLinearAtt() { return 0.0f; }
		virtual float getQuadraticAtt() { return 0.0f; }
		virtual glm::vec3 getPosition() { return glm::vec3(0.0f); }
		virtual float getCutOff() { return 0.0f; }
		virtual float getOuterCutOff() { return 0.0f; }
		virtual glm::vec3 getDirection() { return glm::vec3(0.0f); }
	private:
		glm::vec3 lightColor;
		int isOn = 1;
	protected:
		LightType lightType;
};

class DirectionLight : public Light {
	private:
		glm::vec3 direction;
	public:
		DirectionLight(glm::vec3 lightColor, glm::vec3 direction)
			: Light(LightType::DIRECTION, lightColor) {
			this->direction = direction;
		}
		glm::vec3 getDirection() override {
			return this->direction;
		}
};

class PointLight : public Light {
private:
	float constant;
	float linear;
	float quadratic;
	glm::vec3 position;
public:
	PointLight(glm::vec3 position, glm::vec3 lightColor, float constant, float linear, float quadratic)
		: Light(LightType::POINT, lightColor) {
		this->constant = constant;
		this->linear = linear;
		this->quadratic = quadratic;
		this->position = position;
	}

	float getConstantAtt() override {
		return this->constant;
	}

	float getLinearAtt() override {
		return this->linear;
	}

	float getQuadraticAtt() override {
		return this->quadratic;
	}

	glm::vec3 getPosition() override {
		return this->position;
	}
};

class SpotLight : public PointLight {
	private:
		glm::vec3 direction;
		float cutOff;
		float outerCutOff;
	public:
		SpotLight(glm::vec3 position, glm::vec3 lightColor, glm::vec3 direction, float cutOff, float outerCutOff, float constant, float linear, float quadratic)
			: PointLight(position, lightColor, constant, linear, quadratic) {
			this->direction = direction;
			this->cutOff = cutOff;
			this->outerCutOff = outerCutOff;
			this->lightType = LightType::SPOT;
		}
		float getCutOff() override {
			return this->cutOff;
		}

		float getOuterCutOff() override {
			return this->outerCutOff;
		}

		glm::vec3 getDirection() override {
			return this->direction;
		}	
};

class FlashLight : public SpotLight {
	private:
		bool lightSwitchOnOff = true;
	public:
		FlashLight(glm::vec3 position, glm::vec3 lightColor, glm::vec3 direction, float cutOff, float outerCutOff, float constant, float linear, float quadratic)
			: SpotLight(position, lightColor, direction, cutOff, outerCutOff, constant, linear, quadratic) {
			this->lightType = LightType::FLASHLIGHT;
		}
		void processTurnOffOn(GLFWwindow* window) {
			if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
				if (!lightSwitchOnOff) { 
					toggleOnOff();    
					lightSwitchOnOff = true;  
				}
			}
			else {
				lightSwitchOnOff = false;
			}
		}
};

