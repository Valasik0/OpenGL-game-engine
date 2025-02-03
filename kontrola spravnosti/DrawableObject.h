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
#include "Model.h"
#include "Transformation.h"
#include "Shader.h"
#include "Material.h"

class DrawableObject
{
	Model* model;
	Composite transformations;  //container of transformations
	Shader* shader;
	

public:
	DrawableObject(Model* model, Shader* shader, Material* material);
	DrawableObject(const float points[], GLint vertexSize, int verticesCount, Shader* shader, Material* material);
	DrawableObject(const float points[], GLint vertexSize, int verticesCount, Shader* shader);
	void transform();
	void addTransformation(Transformation* t);
	void setLight(glm::vec3 lightPostion, glm::vec3 lightColor, glm::vec3 cameraPosition);
	void setMaterial();
	void useProg();
	void drawArrays();
	void bindArray();
	Shader& getShader();
	Material* material;
};

