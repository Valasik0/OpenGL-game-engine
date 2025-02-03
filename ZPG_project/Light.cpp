#include "Light.h"

Light::Light(LightType lightType, glm::vec3 lightColor){
	this->lightColor = lightColor;
	this->lightType = lightType;

}

void Light::updateColor(glm::vec3 newColor) {
	this->lightColor = newColor;
	notify(this, ChangeType::LightColorChanged);
}

glm::vec3 Light::getLightColor() {
	return this->lightColor;
}

LightType Light::getLightType() {
	return this->lightType;
}

void Light::toggleOnOff() {
	isOn *= -1;
	notify(this, ChangeType::LightTurnedOffOn);
}

int Light::isLightOn() {
	return isOn;
}

void Light::update(void* object) {}