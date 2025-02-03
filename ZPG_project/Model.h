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
#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags
#include "vector"
#include "Shader.h"
#include "Composite.h"

#define MODEL_PATH_TERRAIN "./Objects/teren/teren.obj"
#define MODEL_PATH_CAT "./Objects/cat/cat.obj"
#define MODEL_PATH_HOUSE "./Objects/house/model.obj"
#define MODEL_PATH_ZOMBIE "./Objects/zombie/zombie.obj"
#define MODEL_PATH_TREE "./Objects/tree/tree.obj"
#define MODEL_PATH_TOWER "./Objects/tower/wooden watch tower2.obj"

enum class ModelLoadedType {
	TERRAIN,
	ZOMBIE,
	HOUSE,
	CAT,
	TREE,
	TOWER,
	NONE
};

class Model
{
	public:
		Model(const float points[], GLint size, int verticesCount, Shader* shader);
		Model(std::string modelPath, Shader* shader, ModelLoadedType type);
		void initModel();
		void bindArray();
		int getVerticesCount();
		std::string getModelPath();
		ModelLoadedType getModelType();
	private:
		GLuint VAO;
		GLuint VBO;
		GLuint IBO;
		GLint vertexSize;
		Shader* shader;
		int verticesCount;
		const float* points;
		std::string modelPath;
		void loadModel(std::string modelPath);
		ModelLoadedType modelType;
};

