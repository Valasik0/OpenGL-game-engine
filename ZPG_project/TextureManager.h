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
#include <string>
#include <SOIL.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

#define TEXTURE_PATH_GRASS "./Textures/grass.png"
#define TEXTURE_PATH_CAT "./Textures/Cat_diffuse.jpg"
#define TEXTURE_PATH_HOUSE "./Objects/house/model.png"
#define TEXTURE_PATH_ZOMBIE "./Objects/zombie/zombie.png"
#define TEXTURE_PATH_TREE "./Textures/tree.png"
#define TEXTURE_PATH_TOWER "./Textures/Wood_tower_Col.jpg"

#define TEXTURE_PATH_SKYBOX_POSX "./Textures/Skybox/posx.jpg"
#define TEXTURE_PATH_SKYBOX_NEGX "./Textures/Skybox/negx.jpg"
#define TEXTURE_PATH_SKYBOX_POSY "./Textures/Skybox/posy.jpg"
#define TEXTURE_PATH_SKYBOX_NEGY "./Textures/Skybox/negy.jpg"
#define TEXTURE_PATH_SKYBOX_POSZ "./Textures/Skybox/posz.jpg"
#define TEXTURE_PATH_SKYBOX_NEGZ "./Textures/Skybox/negz.jpg"


class TextureManager
{
private:
	static TextureManager* instance;
	std::vector<int> textures;
	TextureManager();
	static int texturesCount;
	int latestTextureID = -1;
public:
	static TextureManager* getInstance();
	void addTexture(const char* texturePath);
	int getLatestTextureID();
	void loadCubeMap(std::vector<std::string> skybox);
};



