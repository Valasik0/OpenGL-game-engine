#include "Scene.h"
Scene::Scene() {}

void Scene::addObject(DrawableObject* o) {
	this->objects.push_back(o);
}

void Scene::addLight(Light* l) {
	this->lights.push_back(l);
}

void Scene::setCamera(Camera* camera) {
	this->camera = camera;
}

Camera* Scene::getCamera() {
	return this->camera;
}

void Scene::loadShaders() {
	Shader* shader_phong = new ShaderPhong(LIGHT_VERTEX, PHONG_);
	Shader* shader_blinn = new ShaderBlinn(LIGHT_VERTEX, BLINN_);
	Shader* shader_lambert = new ShaderLambert(LIGHT_VERTEX, LAMBERT_);
	Shader* shader_constant = new ShaderConstant(COLOR_VERTEX, CONSTANT_);
	Shader* shader_color = new ShaderClassic(COLOR_VERTEX, COLOR_FRAGMENT);
	Shader* shader_texture = new ShaderTexture(TEXTURE_VERTEX, TEXTURE_);
	Shader* shader_skybox = new ShaderCubemap(SKYBOX_VERTEX, SKYBOX);

	this->shaders.push_back(shader_phong);
	this->shaders.push_back(shader_blinn);
	this->shaders.push_back(shader_lambert);
	this->shaders.push_back(shader_constant);
	this->shaders.push_back(shader_color);
	this->shaders.push_back(shader_texture);
	this->shaders.push_back(shader_skybox);
}

void Scene::addShader(Shader* shader) {
	this->shaders.push_back(shader);
}

Shader* Scene::getShaderByType(ShaderType type) {
	for (Shader* s : this->shaders) {
		if (s->getShaderType() == type) {
			return s;
		}
	}
}


void Scene::loadModels() {
	Model* model_terrain = new Model(MODEL_PATH_TERRAIN, this->getShaderByType(ShaderType::TEXTURE), ModelLoadedType::TERRAIN);
	Model* model_tree = new Model(MODEL_PATH_TREE, this->getShaderByType(ShaderType::TEXTURE), ModelLoadedType::TREE);
	Model* model_zombie = new Model(MODEL_PATH_ZOMBIE, this->getShaderByType(ShaderType::TEXTURE), ModelLoadedType::ZOMBIE);
	Model* model_house = new Model(MODEL_PATH_HOUSE, this->getShaderByType(ShaderType::TEXTURE), ModelLoadedType::HOUSE);
	Model* model_tower = new Model(MODEL_PATH_TOWER, this->getShaderByType(ShaderType::TEXTURE), ModelLoadedType::TOWER);
	Model* model_cat = new Model(MODEL_PATH_CAT, this->getShaderByType(ShaderType::TEXTURE), ModelLoadedType::CAT);

	this->models.push_back(model_terrain);
	this->models.push_back(model_tree);
	this->models.push_back(model_zombie);
	this->models.push_back(model_house);
	this->models.push_back(model_tower);
	this->models.push_back(model_cat);
	
}

void Scene::addModel(Model* model) {
	this->models.push_back(model);
}

Model* Scene::getModelByType(ModelLoadedType type) {
	for (Model* m : this->models) {
		if (m->getModelType() == type) {
			return m;
		}
	}
}

void Scene::loadMaterials() {

	std::vector <std::string> skyboxPath;
	skyboxPath.push_back(TEXTURE_PATH_SKYBOX_POSX);
	skyboxPath.push_back(TEXTURE_PATH_SKYBOX_NEGX);
	skyboxPath.push_back(TEXTURE_PATH_SKYBOX_POSY);
	skyboxPath.push_back(TEXTURE_PATH_SKYBOX_NEGY);
	skyboxPath.push_back(TEXTURE_PATH_SKYBOX_POSZ);
	skyboxPath.push_back(TEXTURE_PATH_SKYBOX_NEGZ);

	if (this->materials.empty()) {
		materials["skybox"] = new Material(skyboxPath);
		materials["wooden_fence"] = new Material();
		materials["grass"] = new Material(TEXTURE_PATH_GRASS);
		materials["house"] = new Material(TEXTURE_PATH_HOUSE);
		materials["zombie"] = new Material(TEXTURE_PATH_ZOMBIE);
		materials["cat"] = new Material(TEXTURE_PATH_CAT);
		materials["tower"] = new Material(TEXTURE_PATH_TOWER);
		materials["tree"] = new Material(TEXTURE_PATH_TREE);
		materials["phong"] = new Material(glm::vec3(0.0, 0.647, 0.0), 0.5f, glm::vec3(0.2, 0.2, 0.2), 0.8f);
		materials["lambert"] = new Material(glm::vec3(0.0, 0.647, 0.0), glm::vec3(0.0, 0.2, 0.0), 0.8f);
		materials["classic"] = new Material();
		materials["red"] = new Material(glm::vec3(1, 0, 0));
		materials["green"] = new Material(glm::vec3(0, 1, 0));
		materials["blue"] = new Material(glm::vec3(0, 0, 1));
	}
}

void Scene::addMaterial(std::string name, Material* material) {
	this->materials.insert({ name.c_str(), material});
}

Material* Scene::getMaterialByType(std::string materialName) {
	for (const auto& pair : this->materials) {
		if (pair.first == materialName) {
			return pair.second;
		}
	}
}

void Scene::objectIdentification(GLFWwindow* window) {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	glViewport(0, 0, width, height);

	GLbyte color[4];
	GLfloat depth;
	GLuint index;

	int newy = height - ypos - 1;

	glReadPixels(xpos, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
	glReadPixels(xpos, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
	glReadPixels(xpos, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

	printf("Clicked on pixel %f, %f, color %02hhx%02hhx%02hhx%02hhx, depth % f, stencil index % u\n",
		xpos, ypos, color[0], color[1], color[2], color[3], depth, index);

	glm::vec3 screenCoord = glm::vec3(xpos, ypos, depth);
	glm::mat4 viewMatrix = this->getCamera()->getView();
	glm::mat4 projectionMatrix = this->getCamera()->getProjection();

	// Invert ypos to match OpenGL coordinates
	screenCoord.y = height - ypos - 1;

	glm::vec4 viewport = glm::vec4(0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height));
	glm::vec3 worldCoord = glm::unProject(screenCoord, viewMatrix, projectionMatrix, viewport);

	this->objIndex = index;
	this->worldCoord = worldCoord;

	printf("unProject [%f,%f,%f]\n", worldCoord.x, worldCoord.y, worldCoord.z);
}

void Scene::spawnObject(GLFWwindow* window) {
	this->objectIdentification(window);

	DrawableObject* new_tree = new DrawableObject(this->getModelByType(ModelLoadedType::TREE), this->getShaderByType(ShaderType::TEXTURE), this->getMaterialByType("tree"));
	float random_scale = static_cast<float>(std::rand()) / RAND_MAX;
	random_scale = 0.2f + random_scale * 1.5f;

	new_tree->addTransformation(new TransformationScale(glm::vec3(random_scale)));
	new_tree->addTransformation(new TransformationTranslate(glm::vec3(this->worldCoord.x, this->worldCoord.y, this->worldCoord.z)));

	this->addObject(new_tree);

	new_tree->useProg();
	this->getCamera()->addObserver(&new_tree->getShader());
	new_tree->setMaterial();
	new_tree->setLight(this->lights, this->getCamera());

	this->getCamera()->updateCamera();
	printf("Object added");
}

void Scene::removeObject(GLFWwindow* window) {
	this->objectIdentification(window);
	if (this->objIndex != 0) {
		this->objects.erase(this->objects.begin() + this->objIndex - 1);
		printf("Object removed");
	}
}

void Scene::highlightObject(GLFWwindow* window) {
	this->objectIdentification(window);
	if (this->objIndex != 0) {
		this->highlightedObject = this->objects[this->objIndex - 1];
		this->highlightedObject->highlightObject(2.5f);
		printf("Object ahoj");
	}
}

void Scene::addMovementPoint(GLFWwindow* window, char type) {
	this->objectIdentification(window);
	this->highlightedObject->setMovement(this->worldCoord, type);
	std::cout << glm::to_string(this->worldCoord) << std::endl;
}