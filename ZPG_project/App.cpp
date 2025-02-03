#include "App.h"
#include "Model.h"
#include "Shader.h"
#include "Models/sphere.h"
#include "Models/plain.h"
#include "Models/suzi_flat.h"
#include "Models/suzi_smooth.h"
#include "Models/tree.h"
#include "Models/bushes.h"
#include "Models/skycube.h"
#include "Models/gift.h"
#include "Models/triangle.h"
#include "Models/skydome.h"
#include "Models/building.h"
#include "Callback.h"
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>
#include <SOIL.h>
//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include "Composite.h"
#include "TransformationRotate.h"
#include "TransformationScale.h"
#include "TransformationTranslate.h"
#include "Camera.h"
#include "DrawableObject.h"
#include "Subject.h"
#include "vector"
#include <ctime>
#include <cstdlib>
#include <string>
#include <tuple>
#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags

App::App() {
	this->window = nullptr;
	this->callback = nullptr;
};

void App::printInfo() {
	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(this->window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);
}

void App::initWindow() {
	glfwSetErrorCallback(this->callback->error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	this->window = glfwCreateWindow(1920, 1080, "ZPG", NULL, NULL);
	if (!this->window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();
}

void App::chooseScene() {
	std::cout << "Select a scene:" << std::endl;
	std::cout << "1. Phong test scene - 4 spheres" << std::endl;
	std::cout << "2. Rotations test scene" << std::endl;
	std::cout << "3. Light crop test scene" << std::endl;
	std::cout << "4. Window resize test scene" << std::endl;
	std::cout << "5. Many objects/many shaders test scene" << std::endl;
	std::cout << "Enter the number of your choice: ";
	std::cin >> this->choice;
}

void App::runApp() {
	chooseScene();
	initWindow();
	printInfo();

	glm::vec3 cameraPos = glm::vec3(0.0f, 2.0f, 20.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	Camera* camera = new Camera(cameraPos, cameraFront, cameraUp, this->window);
	Scene* scene = new Scene();

	Callback& callback = Callback::getInstance();
	callback.initCallbacks(this->window, camera, scene);

	
	this->scene = scene;
	this->scene->setCamera(camera);
	this->scene->loadShaders();
	this->scene->loadModels();
	this->scene->loadMaterials();

	float lightConstant = 1.0f;
	float lightLinear = 0.022f;
	float lightQuadratic = 0.0019f;

	Light* dirLight = new DirectionLight(glm::vec3(0.15f, 0.15f, 0.15f), glm::vec3(0.0f, -1.0f, 0.0f));
	Light* pointLight = new PointLight
	(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(1.0f, 1.0f, 1.0f), lightConstant, lightLinear, lightQuadratic);
	Light* pointLight2 = new PointLight
	(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), lightConstant, lightLinear, lightQuadratic);
	Light* pointLight3 = new PointLight
	(glm::vec3(-10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.5f, 0.5f), lightConstant, lightLinear, lightQuadratic);
	Light* spotLight = new SpotLight
	(glm::vec3(12.0f, 5.0f, 5.0f), glm::vec3(1.0f, 0.6f, 0.6f), glm::vec3(1.0f, -0.6f, 0.7f), glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f)), lightConstant, lightLinear, lightQuadratic);
	Light* spotLight2 = new SpotLight
	(glm::vec3(-12.0f, 7.0f, -12.0f), glm::vec3(0.2f, 0.3f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f)), lightConstant, lightLinear, lightQuadratic);
	FlashLight* flashLight = new FlashLight
	(cameraPos, glm::vec3(1.0f, 1.0f, 1.0f), cameraFront, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f)), lightConstant, lightLinear, lightQuadratic);

	Light* phongCropLight = new PointLight
	(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(1.0f, 1.0f, 1.0f), lightConstant, lightLinear, lightQuadratic);
	Light* phongTestLight = new PointLight
	(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(1.0f, 1.0f, 1.0f), lightConstant, lightLinear, lightQuadratic);

	//--------------------------------------------PHONG------------------------------------------------
	DrawableObject* object_sphere0 = new DrawableObject(sphere, 6, 2880, this->scene->getShaderByType(ShaderType::PHONG), this->scene->getMaterialByType("phong"));
	object_sphere0->addTransformation(new TransformationTranslate(glm::vec3(-2.0f, 0.0f, -5.0f)));

	DrawableObject* object_sphere1 = new DrawableObject(sphere, 6, 2880, this->scene->getShaderByType(ShaderType::PHONG), this->scene->getMaterialByType("phong"));
	object_sphere1->addTransformation(new TransformationTranslate(glm::vec3(2.0f, 0.0f, -5.0f)));

	DrawableObject* object_sphere2 = new DrawableObject(sphere, 6, 2880, this->scene->getShaderByType(ShaderType::PHONG), this->scene->getMaterialByType("phong"));
	object_sphere2->addTransformation(new TransformationTranslate(glm::vec3(0.0f, 2.0f, -5.0f)));

	DrawableObject* object_sphere3 = new DrawableObject(sphere, 6, 2880, this->scene->getShaderByType(ShaderType::PHONG), this->scene->getMaterialByType("phong"));
	object_sphere3->addTransformation(new TransformationTranslate(glm::vec3(0.0f, -2.0f, -5.0f)));
	//-----------------------------------------------------------------------------------------------------


	DrawableObject* halo_sphere = new DrawableObject(sphere, 6, 2880, this->scene->getShaderByType(ShaderType::PHONG), this->scene->getMaterialByType("phong"));
	halo_sphere->addTransformation(new TransformationTranslate(glm::vec3(0.0f, 0.0f, 0.0f)));
	
	//------------------------------------PLANETS---------------------------------------
	Shader* shader_yellow = new ShaderConstant(COLOR_VERTEX, CONSTANT_);
	Material* material_yellow = new Material(glm::vec3(1, 1, 0));
	DrawableObject* sun = new DrawableObject(sphere, 6, 2880, shader_yellow, material_yellow);
	sun->addTransformation(new TransformationScale(glm::vec3(1.2)));
	sun->addTransformation(new TransformationTranslate(glm::vec3(0.0f, 0.0f, 1.0f)));

	Shader* shader_blue = new ShaderConstant(COLOR_VERTEX, CONSTANT_);
	DrawableObject* planet = new DrawableObject(sphere, 6, 2880, shader_blue, this->scene->getMaterialByType("blue"));
	planet->addTransformation(new TransformationScale(glm::vec3(0.4)));
	planet->addTransformation(new TransformationTranslate(glm::vec3(0.0f, 0.0f, 3.0f)));
	planet->addTransformation(new TransformationRotate(0.3f, glm::vec3(0.0f, 1.0f, 0.0f), true));
	planet->addTransformation(sun->getTransformations());

	Shader* shader_cyan = new ShaderConstant(COLOR_VERTEX, CONSTANT_);
	Material* material_cyan = new Material(glm::vec3(0.0, 1.0, 0.8));
	DrawableObject* planet1 = new DrawableObject(sphere, 6, 2880, shader_cyan, material_cyan);
	planet1->addTransformation(new TransformationScale(glm::vec3(0.3)));
	planet1->addTransformation(new TransformationTranslate(glm::vec3(0.0f, 0.0f, 5.0f)));
	planet1->addTransformation(new TransformationRotate(1.2f, glm::vec3(0.0f, 1.0f, 0.0f), true));
	planet1->addTransformation(sun->getTransformations());

	DrawableObject* planet2 = new DrawableObject(sphere, 6, 2880, shader_blue, this->scene->getMaterialByType("blue"));
	planet2->addTransformation(new TransformationScale(glm::vec3(0.8)));
	planet2->addTransformation(new TransformationTranslate(glm::vec3(0.0f, 0.0f, 7.0f)));
	planet2->addTransformation(new TransformationRotate(3.5f, glm::vec3(0.0f, 1.0f, 0.0f), true));
	planet2->addTransformation(sun->getTransformations());
	
	Shader* shader_grey = new ShaderConstant(COLOR_VERTEX, CONSTANT_);
	Material* material_grey = new Material(glm::vec3(0.3, 0.3, 0.3));
	DrawableObject* moon = new DrawableObject(sphere, 6, 2880, shader_grey, material_grey);
	moon->addTransformation(new TransformationScale(glm::vec3(0.8)));
	moon->addTransformation(new TransformationTranslate(glm::vec3(0.0f, 0.0f, 6.0f)));
	moon->addTransformation(new TransformationRotate(20.0f, glm::vec3(0.0f, 1.0f, 0.0f), true));
	moon->addTransformation(planet1->getTransformations());

	DrawableObject* my_skybox = new DrawableObject(skycube, 3, 36, this->scene->getShaderByType(ShaderType::CUBEMAP), this->scene->getMaterialByType("skybox"));

	DrawableObject* my_plain = new DrawableObject(this->scene->getModelByType(ModelLoadedType::TERRAIN), this->scene->getShaderByType(ShaderType::TEXTURE), this->scene->getMaterialByType("grass"));
	my_plain->addTransformation(new TransformationScale(glm::vec3(2.0f)));
	DrawableObject* my_house = new DrawableObject(this->scene->getModelByType(ModelLoadedType::HOUSE), this->scene->getShaderByType(ShaderType::TEXTURE), this->scene->getMaterialByType("house"));
	DrawableObject* my_zombie = new DrawableObject(this->scene->getModelByType(ModelLoadedType::ZOMBIE), this->scene->getShaderByType(ShaderType::TEXTURE), this->scene->getMaterialByType("zombie"));
	DrawableObject* my_cat = new DrawableObject(this->scene->getModelByType(ModelLoadedType::CAT), this->scene->getShaderByType(ShaderType::TEXTURE), this->scene->getMaterialByType("cat"));

	my_cat->addTransformation(new TransformationScale(glm::vec3(0.02f)));
	my_cat->addTransformation(new TransformationRotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f), false));
	my_cat->addTransformation(new TransformationTranslate(glm::vec3(0.0f, 0.0f, 12.0f)));

	DrawableObject* my_tower = new DrawableObject(this->scene->getModelByType(ModelLoadedType::TOWER), this->scene->getShaderByType(ShaderType::TEXTURE), this->scene->getMaterialByType("tower"));
	my_tower->addTransformation(new TransformationScale(glm::vec3(1.2f)));
	my_tower->addTransformation(new TransformationTranslate(glm::vec3(10.0f, -0.7f, 0.0f)));

	DrawableObject* my_tree = new DrawableObject(this->scene->getModelByType(ModelLoadedType::TREE), this->scene->getShaderByType(ShaderType::TEXTURE), this->scene->getMaterialByType("tree"));
	DrawableObject* my_bush = new DrawableObject(bushes, 6, 8730, this->scene->getShaderByType(ShaderType::LAMBERT), this->scene->getMaterialByType("lambert"));

	switch (this->choice) {
	case 1:
		
		scene->addLight(flashLight);
		scene->addLight(phongTestLight);
		scene->addObject(object_sphere0);
		scene->addObject(object_sphere1);
		scene->addObject(object_sphere2);
		scene->addObject(object_sphere3);	
		
		break;
	case 2:
		scene->addObject(sun);
		scene->addObject(planet);
		scene->addObject(planet1);
		scene->addObject(planet2);
		scene->addObject(moon);
		break;
	case 3:
		scene->addLight(flashLight);
		scene->addLight(phongCropLight);
		scene->addObject(halo_sphere);
		break;
	case 4:
		scene->addObject(halo_sphere);
		break;
	case 5:
		
		std::srand(static_cast<unsigned>(std::time(nullptr)));
		scene->addLight(flashLight);
		scene->addLight(dirLight);
		scene->addLight(pointLight);
		scene->addLight(pointLight2);
		scene->addLight(pointLight3);
		scene->addLight(spotLight);
		scene->addLight(spotLight2);

		scene->addObject(my_plain);
		
		scene->addObject(my_house);
		scene->addObject(my_tower);
		scene->addObject(my_cat);
		

		for (int i = 0; i < 100; i++) {	
			float x = -50 + (std::rand() % (-50 - 50 + 1));
			float z = -50 + (std::rand() % (-50 - 50 + 1));
			float random_scale = static_cast<float>(std::rand()) / RAND_MAX;
			random_scale = 0.1 + random_scale * 1.2f;
			float random_angle = rand() % 361;

			std::vector<DrawableObject*> my_objects;

			my_objects.push_back(my_bush);
			my_objects.push_back(my_tree);
			my_objects.push_back(my_zombie);
			
			int random_object_i = std::rand() % my_objects.size();

			DrawableObject* my_object = new DrawableObject(*my_objects[random_object_i]);

			my_object->addTransformation(new TransformationScale(glm::vec3(random_scale)));
			my_object->addTransformation(new TransformationRotate(random_angle, glm::vec3(0.0f, 1.0f, 0.0f), false));
			my_object->addTransformation(new TransformationTranslate(glm::vec3(x, 0.0f, z)));

			scene->addObject(my_object);
		}
		break;
	default:
		std::cout << "Invalid choice. Please enter a valid number." << std::endl;
		break;
	}

	for (DrawableObject* o : scene->objects) {
		o->useProg();
		this->scene->getCamera()->addObserver(&o->getShader());
		flashLight->addObserver(&o->getShader());
		o->setMaterial();
		o->setLight(this->scene->lights, this->scene->getCamera());
	}

	my_skybox->useProg();
	this->scene->getCamera()->addObserver(&my_skybox->getShader());
	my_skybox->setMaterial();

	this->scene->getCamera()->updateCamera();
	this->scene->getCamera()->setMouseInput(this->window);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	while (!glfwWindowShouldClose(this->window)) {	
		
		this->scene->getCamera()->processInput(this->window);
		flashLight->processTurnOffOn(this->window);
		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		my_skybox->useProg();
		my_skybox->setMaterial();
		glStencilFunc(GL_ALWAYS, 0, 0xFF);
		my_skybox->bindArray();
		my_skybox->drawArrays();
		glClear(GL_DEPTH_BUFFER_BIT);

		int objIndex = 1;

		for (DrawableObject* o : scene->objects) {
			o->useProg();			
			o->transform();
			o->setMaterial();
			glStencilFunc(GL_ALWAYS, objIndex, 0xFF);
			o->bindArray();	
			o->drawArrays();	
			objIndex++;
		}

		
		glfwPollEvents();
		glfwSwapBuffers(this->window);
	}
	glfwDestroyWindow(this->window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}