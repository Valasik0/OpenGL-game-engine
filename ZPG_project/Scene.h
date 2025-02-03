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
#include "vector"
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include "DrawableObject.h"
#include "Light.h"
#include "Camera.h"
#include "map"
#include "TransformationScale.h"
#include "TransformationRotate.h"
#include "TransformationTranslate.h"
#include "TransformationBezier.h"
#include "Transformation.h"

class Scene
{
	public:
		Scene();
		void addObject(DrawableObject* o);
		void addLight(Light* l);
		std::vector<DrawableObject*> objects;
		std::vector<Light*> lights;
		void setCamera(Camera* camera);
		Camera* getCamera();
		void spawnObject(GLFWwindow* window);
		void removeObject(GLFWwindow* window);

		void loadShaders();
		void addShader(Shader* shader);
		Shader* getShaderByType(ShaderType type);
		
		void loadModels();
		void addModel(Model* model);
		Model* getModelByType(ModelLoadedType type);

		void loadMaterials();
		void addMaterial(std::string name, Material* material);
		Material* getMaterialByType(std::string materialName);

		void highlightObject(GLFWwindow* window);
		void addMovementPoint(GLFWwindow* window, char type);

	private:
		Camera* camera;
		vector<Shader*> shaders;
		vector<Model*> models;
		std::map<std::string, Material*> materials;
		void objectIdentification(GLFWwindow* window);
		GLint objIndex;
		glm::vec3 worldCoord;
		DrawableObject* highlightedObject;
};

