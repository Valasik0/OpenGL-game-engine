#include "TextureManager.h"

TextureManager* TextureManager::instance = 0;

int TextureManager::texturesCount = 1;

TextureManager::TextureManager() {};

TextureManager* TextureManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new TextureManager();
	}
	return instance;
}

void TextureManager::addTexture(const char* texturePath)
{
	glActiveTexture(GL_TEXTURE1 + texturesCount);
	this->texturesCount++;

	GLuint textureID = SOIL_load_OGL_texture(texturePath, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (textureID == NULL) {
		std::cout << "An error occurred while loading texture." << std::endl;
		exit(EXIT_FAILURE);
	}

	this->textures.push_back(textureID);
	this->latestTextureID = textureID;

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

int TextureManager::getLatestTextureID() {
	return this->latestTextureID;
}

void TextureManager::loadCubeMap(std::vector<std::string> skybox)
{
	glActiveTexture(GL_TEXTURE0);
	GLuint textureID = SOIL_load_OGL_cubemap
	(skybox[0].c_str(),
	skybox[1].c_str(),
	skybox[2].c_str(),
	skybox[3].c_str(),
	skybox[4].c_str(),
	skybox[5].c_str(),
	SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	if (textureID == NULL) {
		std::cout << "An error occurred while loading CubeMap." << std::endl;
		exit(EXIT_FAILURE);
	}

	glBindTexture(GL_TEXTURE_2D, textureID);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

