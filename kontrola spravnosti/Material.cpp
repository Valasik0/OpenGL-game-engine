#include "Material.h"
Material::Material(glm::vec3 objectColor, float specular, glm::vec3 ambient, float diffuse) {
	this->objectColor = objectColor;
	this->specular = specular;
	this->ambient = ambient;
	this->diffuse = diffuse;
}

Material::Material(glm::vec3 objectColor, glm::vec3 ambient, float diffuse) {
	this->objectColor = objectColor;
	this->specular = specular = 0.0f;
	this->ambient = ambient = ambient;
	this->diffuse = diffuse = diffuse;
}

Material::Material(glm::vec3 objectColor) {
	this->objectColor = objectColor;
	this->specular = specular = 0.0f;
	this->ambient = ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	this->diffuse = diffuse = 0.0f;
}

Material::Material() {
	this->objectColor = glm::vec3(0.0f, 0.0f, 0.0f);
	this->specular = specular = 0.0f;
	this->ambient = ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	this->diffuse = diffuse = 0.0f;
}

float Material::getSpecular() {
    return this->specular;
}

glm::vec3 Material::getAmbient() {
    return this->ambient;
}

float Material::getDiffuse() {
    return this->diffuse;
}

glm::vec3 Material::getObjectColor(){
    return this->objectColor;
}