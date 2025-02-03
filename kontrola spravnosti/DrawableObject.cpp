#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* model, Shader* shader, Material* material) {
	this->shader = shader;
	this->model = model;
	this->material = material;
	this->model->initModel();
}

DrawableObject::DrawableObject(const float points[], GLint vertexSize, int verticesCount, Shader * shader, Material* material) {
	this->shader = shader;
	this->model = new Model(points, vertexSize, verticesCount, shader);
	this->material = material;
	this->model->initModel();
}

DrawableObject::DrawableObject(const float points[], GLint vertexSize, int verticesCount, Shader* shader) {
	this->shader = shader;
	this->model = new Model(points, vertexSize, verticesCount, shader);
	this->material = nullptr;
	this->model->initModel();
}

Shader& DrawableObject::getShader() {
	return *this->shader;
}

void DrawableObject::transform() {
	this->shader->passUniformLocation(this->transformations.traverse(), "modelMatrix");
}

void DrawableObject::addTransformation(Transformation* t) {
	this->transformations.add(t);
}

void DrawableObject::setLight(glm::vec3 lightPostion, glm::vec3 lightColor, glm::vec3 cameraPosition) {
	this->shader->passUniformLocation(lightPostion, "lightPosition");
	this->shader->passUniformLocation(cameraPosition, "cameraPosition");
	this->shader->passUniformLocation(lightColor, "lightColor");
}


void DrawableObject::setMaterial() {
	this->shader->useProgram();
	if (this->shader->getShaderType() == ShaderType::PHONG) {
		this->shader->passUniformLocation(this->material->getAmbient(), "ambientColor");
		this->shader->passUniformLocation(this->material->getObjectColor(), "objectColor");
		this->shader->passUniformLocation(this->material->getSpecular(), "specularStrength");
		this->shader->passUniformLocation(this->material->getDiffuse(), "diffuseStrength");
	}
	if (this->shader->getShaderType() == ShaderType::LAMBERT) {
		this->shader->passUniformLocation(this->material->getAmbient(), "ambientColor");
		this->shader->passUniformLocation(this->material->getObjectColor(), "objectColor");
		this->shader->passUniformLocation(this->material->getDiffuse(), "diffuseStrength");
		
	}
	if (this->shader->getShaderType() == ShaderType::CONSTANT) {
		this->shader->passUniformLocation(this->material->getObjectColor(), "objectColor");
	}
	if (this->shader->getShaderType() == ShaderType::CLASSIC) {}
}

void DrawableObject::useProg() {
	this->shader->useProgram();
}

void DrawableObject::drawArrays() {
	glDrawArrays(GL_TRIANGLES, 0, this->model->getVerticesCount());
}

void DrawableObject::bindArray() {
	this->model->bindArray();
}