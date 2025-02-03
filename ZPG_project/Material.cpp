#include "Material.h"
Material::Material(glm::vec3 objectColor, float specular, glm::vec3 ambient, float diffuse) {
	this->objectColor = objectColor;
	this->specular = specular;
	this->ambient = ambient;
	this->diffuse = diffuse;
}

Material::Material(glm::vec3 objectColor, glm::vec3 ambient, float diffuse) {
	this->objectColor = objectColor;
	this->ambient = ambient = ambient;
	this->diffuse = diffuse = diffuse;
}

Material::Material(glm::vec3 objectColor) {
	this->objectColor = objectColor;
}

Material::Material(std::string texturePath) {
	TextureManager* textureManager = TextureManager::getInstance();
	textureManager->addTexture(texturePath.c_str());
	this->textureID = textureManager->getLatestTextureID();
	this->ambient = glm::vec3(0.15f, 0.1f, 0.15f);
	this->specular = 0.5f;
	this->diffuse = 0.8f;
	this->uvMult = 1;
}

Material::Material(std::string texturePath, int uvMult) {
	TextureManager* textureManager = TextureManager::getInstance();
	textureManager->addTexture(texturePath.c_str());
	this->textureID = textureManager->getLatestTextureID();
	this->ambient = glm::vec3(0.15f, 0.1f, 0.15f);
	this->specular = 0.5f;
	this->diffuse = 0.8f;
	this->uvMult = uvMult;
}

Material::Material(std::vector<std::string> skybox) {
	TextureManager* textureManager = TextureManager::getInstance();
	textureManager->loadCubeMap(skybox);
	this->textureID = 0;
}

Material::Material() {
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

GLuint Material::getTextureID() {
	return this->textureID;
}

int Material::getUvMult() {
	return this->uvMult;
}

void Material::highlight() {
	this->ambient *= 1.3f;
	this->specular *= 1.3f;
	this->diffuse *= 1.3f;
}