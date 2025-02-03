#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* model, Shader* shader, Material* material) {
	this->shader = shader;
	this->model = model;
	this->material = material;
	this->highlightCoefficient = 1.0f;
}

DrawableObject::DrawableObject(const float points[], GLint vertexSize, int verticesCount, Shader * shader, Material* material) {
	this->shader = shader;
	this->model = new Model(points, vertexSize, verticesCount, shader);
	this->material = material;
	this->highlightCoefficient = 1.0f;
	this->model->initModel();

	
}

DrawableObject::DrawableObject(const float points[], GLint vertexSize, int verticesCount, Shader* shader) {
	this->shader = shader;
	this->model = new Model(points, vertexSize, verticesCount, shader);
	this->material = nullptr;
	this->highlightCoefficient = 1.0f;
	this->model->initModel();
}

Shader& DrawableObject::getShader() {
	return *this->shader;
}

std::vector<Transformation*> DrawableObject::getTransformations() {
	return this->transformations.children;
}

void DrawableObject::transform() {
	this->shader->passUniformLocation(this->transformations.traverse(), "modelMatrix");
}

void DrawableObject::highlightObject(float coefficient) {
	this->highlightCoefficient = coefficient;
	this->objectHighlighted = true;
	this->shader->useProgram();
	this->shader->passUniformLocation(this->highlightCoefficient, "highlightCoefficient");
}

void DrawableObject::setMovement(glm::vec3 point, char type) {
	if (type == 'b') {
		if (movementPoints.size() < 4) {
			this->movementPoints.push_back(point);
		}
		else if (movementPoints.size() >= 4) {
			if (!transformations.children.empty()) {
				for (Transformation* t : transformations.children) {
					TransformationTranslate* translation = dynamic_cast<TransformationTranslate*>(t);
					TransformationBezier* bezier = dynamic_cast<TransformationBezier*>(t);
					TransformationLine* line = dynamic_cast<TransformationLine*>(t);

					if (translation || bezier || line) {
						transformations.children.erase(std::remove(transformations.children.begin(), transformations.children.end(), t), transformations.children.end());
					}
				}
			}
			this->addTransformation(new TransformationBezier(movementPoints[0], movementPoints[1], movementPoints[2], movementPoints[3]));
			movementPoints.clear();
			this->highlightObject(1.0f);
		}
		
	}
	else if (type == 'l') {
		if (movementPoints.size() < 2) {
			this->movementPoints.push_back(point);
		}
		else if (movementPoints.size() >= 2) {
			if (!transformations.children.empty()) {
				for (Transformation* t : transformations.children) {
					TransformationTranslate* translation = dynamic_cast<TransformationTranslate*>(t);
					TransformationBezier* bezier = dynamic_cast<TransformationBezier*>(t);
					TransformationLine* line = dynamic_cast<TransformationLine*>(t);

					if (translation || bezier || line) {
						transformations.children.erase(std::remove(transformations.children.begin(), transformations.children.end(), t), transformations.children.end());
					}
				}
			}
			this->addTransformation(new TransformationLine(movementPoints[0], movementPoints[1]));
			movementPoints.clear();
			this->highlightObject(1.0f);
		}
	}
}


void DrawableObject::addTransformation(Transformation* t) {
	this->transformations.add(t);
}

void DrawableObject::addTransformation(std::vector<Transformation*> transformations) {
	for (Transformation* t : transformations) {
		this->transformations.add(t);
	}
	
}

void DrawableObject::setLight(std::vector<Light*> lights, Camera* camera) {
	for (int i = 0; i < lights.size(); i++) {
		std::string lightUniformName = "lights[" + std::to_string(i) + "]";
		glm::vec3 direction = glm::vec3(0.0f);
		glm::vec3 position = glm::vec3(0.0f);

		if (lights[i]->getLightType() == LightType::FLASHLIGHT) {
			direction = camera->getTarget();
			position = camera->getPosition();
		}
		else {
			direction = lights[i]->getDirection();
			position = lights[i]->getPosition();
		}

		float cutOff = lights[i]->getCutOff();
		float outerCutOff = lights[i]->getOuterCutOff();
		float constant = lights[i]->getConstantAtt();
		float linear = lights[i]->getLinearAtt();
		float quadratic = lights[i]->getQuadraticAtt();
		glm::vec3 color = lights[i]->getLightColor();
		int isOn = lights[i]->isLightOn();

		this->shader->passUniformLocation(static_cast<int>(lights[i]->getLightType()), (lightUniformName + ".type").c_str());
		this->shader->passUniformLocation(isOn, (lightUniformName + ".isOn").c_str());
		this->shader->passUniformLocation(position, (lightUniformName + ".position").c_str());
		this->shader->passUniformLocation(color, (lightUniformName + ".color").c_str());
		this->shader->passUniformLocation(direction, (lightUniformName + ".direction").c_str());
		this->shader->passUniformLocation(constant, (lightUniformName + ".constantAttenuation").c_str());
		this->shader->passUniformLocation(linear, (lightUniformName + ".linearAttenuation").c_str());
		this->shader->passUniformLocation(quadratic, (lightUniformName + ".quadraticAttenuation").c_str());
		this->shader->passUniformLocation(cutOff, (lightUniformName + ".cutOff").c_str());
		this->shader->passUniformLocation(outerCutOff, (lightUniformName + ".outerCutOff").c_str());
	}

	this->shader->passUniformLocation((int)lights.size(), "numLights");
	this->shader->passUniformLocation(camera->getPosition(), "cameraPosition");
}

void DrawableObject::setMaterial() {
	this->shader->useProgram();

	this->shader->passUniformLocation(this->highlightCoefficient, "highlightCoefficient");

	if (this->shader->getShaderType() == ShaderType::TEXTURE) {
		this->shader->passUniformLocation(this->material->getTextureID(), "textureUnitID");
		this->shader->passUniformLocation(this->material->getAmbient(), "ambientColor");
		this->shader->passUniformLocation(this->material->getDiffuse(), "diffuseStrength");
		this->shader->passUniformLocation(this->material->getSpecular(), "specularStrength");
		this->shader->passUniformLocation(this->material->getUvMult(), "uvMult");
	}

	else if (this->shader->getShaderType() == ShaderType::CUBEMAP) {
		this->shader->passUniformLocation(this->material->getTextureID(), "skybox");
	}

	else{
		if (this->shader->getShaderType() != ShaderType::CLASSIC) {
			this->shader->passUniformLocation(this->material->getObjectColor(), "objectColor");
			if (this->shader->getShaderType() != ShaderType::CONSTANT) {
				this->shader->passUniformLocation(this->material->getAmbient(), "ambientColor");
				this->shader->passUniformLocation(this->material->getDiffuse(), "diffuseStrength");
				if (this->shader->getShaderType() != ShaderType::LAMBERT) {
					this->shader->passUniformLocation(this->material->getSpecular(), "specularStrength");
				}
			}
		}
	}
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