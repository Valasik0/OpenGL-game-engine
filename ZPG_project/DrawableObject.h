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
#include "TransformationTranslate.h"
#include "TransformationScale.h"
#include "TransformationBezier.h"
#include "TransformationLine.h"
#include "Shader.h"
#include "Material.h"
#include "Light.h"
#include "Camera.h"
#include "Bezier.h"
#include "vector"

class DrawableObject
{
	Model* model;
	Composite transformations;  //container of transformations
	Shader* shader;
	float highlightCoefficient;
	bool objectHighlighted = false;
	vector<glm::vec3> movementPoints;

public:
	DrawableObject(Model* model, Shader* shader, Material* material);
	DrawableObject(const float points[], GLint vertexSize, int verticesCount, Shader* shader, Material* material);
	DrawableObject(const float points[], GLint vertexSize, int verticesCount, Shader* shader);
	void transform();
	void addTransformation(Transformation* t);
	void addTransformation(std::vector<Transformation*> transformations);
	void setLight(std::vector<Light*> lights, Camera* camera);
	void setMaterial();
	void useProg();
	void drawArrays();
	void bindArray();
	Shader& getShader();
	std::vector<Transformation*> getTransformations();
	Material* material;
	void highlightObject(float coefficient);
	void setMovement(glm::vec3 point, char type);
};

class SkyboxObject : public DrawableObject
{
	SkyboxObject(Model* model, Shader* shader, Material* material) :
		DrawableObject(model, shader, material) {}
};

