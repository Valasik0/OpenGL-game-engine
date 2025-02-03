#include "Light.h"

Light::Light(glm::vec3 lightPosition, glm::vec3 lightColor){
	this->lightPosition = lightPosition;
	this->lightColor = lightColor;
}

void Light::updatePosition(glm::vec3 newPosition) {
	this->lightPosition = newPosition;
	notify(this, ChangeType::LightPositionChanged);
}

void Light::updateColor(glm::vec3 newColor) {
	this->lightColor = newColor;
	notify(this, ChangeType::LightPositionChanged);
}

glm::vec3 Light::getLightPosition() {
	return this->lightPosition;
}

glm::vec3 Light::getLightColor() {
	return this->lightColor;
}

void Light::update(void* object) {}