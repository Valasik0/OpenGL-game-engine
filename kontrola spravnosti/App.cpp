#include "App.h"
#include "Model.h"
#include "Shader.h"
#include "Models/sphere.h"
#include "Models/plain.h"
#include "Models/suzi_flat.h"
#include "Models/suzi_smooth.h"
#include "Models/tree.h"
#include "Models/bushes.h"
#include "Models/gift.h"
#include "Callback.h"
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>

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
#define PHONG_ "./Shaders/Fragment/phong.frag"
#define PHONG_WRONG "./Shaders/Fragment/phong_wrong.frag"
#define LAMBERT_ "./Shaders/Fragment/lambert.frag"
#define LIGHT_VERTEX "./Shaders/Vertex/light.vert"
#define CONSTANT_ "./Shaders/Fragment/constant.frag"
#define COLOR_VERTEX "./Shaders/Vertex/vertex.vert"
#define COLOR_FRAGMENT "./Shaders/Fragment/fragment.frag"

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
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	glm::vec3 cameraPos = glm::vec3(0.0f, 10.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	Camera* camera = new Camera(cameraPos, cameraFront, cameraUp, this->window);
	
	Callback& callback = Callback::getInstance();
	callback.initCallbacks(window, camera);

	Scene* scene = new Scene();

	printInfo();

	std::vector <Shader*> shaders;

	Shader* shader_phong = new ShaderPhong(LIGHT_VERTEX, PHONG_);
	Shader* shader_lambert = new ShaderLambert(LIGHT_VERTEX, LAMBERT_);
	Shader* shader_constant = new ShaderConstant(COLOR_VERTEX, CONSTANT_);
	Shader* shader_color = new ShaderClassic(COLOR_VERTEX, COLOR_FRAGMENT);
	shaders.push_back(shader_phong);
	shaders.push_back(shader_lambert);
	shaders.push_back(shader_constant);
	shaders.push_back(shader_color);

	std::vector <Material*> materials;

	Material* material_phong = new Material(glm::vec3(0.385, 0.647, 0.812), 0.5f, glm::vec3(0.2, 0.2, 0.2), 0.8f);
	Material* material_lambert = new Material(glm::vec3(0.385, 0.647, 0.812), glm::vec3(0.2, 0.2, 0.2), 0.8f);
	Material* material_classic = new Material();
	Material* material_red = new Material(glm::vec3(1, 0, 0));
	Material* material_green = new Material(glm::vec3(0, 1, 0));
	Material* material_blue = new Material(glm::vec3(0, 0, 1));
	materials.push_back(material_red);
	materials.push_back(material_green);
	materials.push_back(material_blue);

	//--------------------------------------------PHONG------------------------------------------------
	DrawableObject* object_sphere0 = new DrawableObject(sphere, 6, 2880, shader_phong, material_phong);
	object_sphere0->addTransformation(new TransformationTranslate(glm::vec3(-2.0f, 0.0f, -5.0f)));

	DrawableObject* object_sphere1 = new DrawableObject(sphere, 6, 2880, shader_phong, material_phong);
	object_sphere1->addTransformation(new TransformationTranslate(glm::vec3(2.0f, 0.0f, -5.0f)));

	DrawableObject* object_sphere2 = new DrawableObject(sphere, 6, 2880, shader_phong, material_phong);
	object_sphere2->addTransformation(new TransformationTranslate(glm::vec3(0.0f, 2.0f, -5.0f)));

	DrawableObject* object_sphere3 = new DrawableObject(sphere, 6, 2880, shader_phong, material_phong);
	object_sphere3->addTransformation(new TransformationTranslate(glm::vec3(0.0f, -2.0f, -5.0f)));
	//-----------------------------------------------------------------------------------------------------


	DrawableObject* halo_sphere = new DrawableObject(sphere, 6, 2880, shader_phong, material_phong);
	halo_sphere->addTransformation(new TransformationTranslate(glm::vec3(0.0f, 0.0f, 0.0f)));
	
	//------------------------------------PLANETS---------------------------------------
	Shader* shader_yellow = new ShaderConstant(COLOR_VERTEX, CONSTANT_);
	Material* material_yellow = new Material(glm::vec3(1, 1, 0));
	DrawableObject* sun = new DrawableObject(sphere, 6, 2880, shader_yellow, material_yellow);
	sun->addTransformation(new TransformationScale(glm::vec3(1.2)));
	sun->addTransformation(new TransformationTranslate(glm::vec3(0.0f, 0.0f, 1.0f)));

	Shader* shader_blue = new ShaderConstant(COLOR_VERTEX, CONSTANT_);
	DrawableObject* planet = new DrawableObject(sphere, 6, 2880, shader_blue, material_blue);
	planet->addTransformation(new TransformationScale(glm::vec3(0.4)));
	planet->addTransformation(new TransformationTranslate(glm::vec3(0.0f, 0.0f, 3.0f)));
	planet->addTransformation(new TransformationRotate(0.3f, glm::vec3(0.0f, 1.0f, 0.0f), true));
	planet->addTransformation(new TransformationTranslate(glm::vec3(0.0f, 0.0f, 1.0f)));

	Shader* shader_cyan = new ShaderConstant(COLOR_VERTEX, CONSTANT_);
	Material* material_cyan = new Material(glm::vec3(0.0, 1.0, 0.8));
	DrawableObject* planet1 = new DrawableObject(sphere, 6, 2880, shader_cyan, material_cyan);
	planet1->addTransformation(new TransformationScale(glm::vec3(0.3)));
	planet1->addTransformation(new TransformationTranslate(glm::vec3(0.0f, 0.0f, 5.0f)));
	planet1->addTransformation(new TransformationRotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f), true));
	planet1->addTransformation(new TransformationTranslate(glm::vec3(0.0f, 0.0f, 1.0f)));

	DrawableObject* planet2 = new DrawableObject(sphere, 6, 2880, shader_blue, material_blue);
	planet2->addTransformation(new TransformationScale(glm::vec3(0.8)));
	planet2->addTransformation(new TransformationTranslate(glm::vec3(0.0f, 0.0f, 7.0f)));
	planet2->addTransformation(new TransformationRotate(0.5f, glm::vec3(0.0f, 1.0f, 0.0f), true));
	planet2->addTransformation(new TransformationTranslate(glm::vec3(0.0f, 0.0f, 1.0f)));
	
	Shader* shader_grey = new ShaderConstant(COLOR_VERTEX, CONSTANT_);
	Material* material_grey = new Material(glm::vec3(0.3, 0.3, 0.3));
	DrawableObject* moon = new DrawableObject(sphere, 6, 2880, shader_grey, material_grey);
	moon->addTransformation(new TransformationScale(glm::vec3(0.1)));
	moon->addTransformation(new TransformationTranslate(glm::vec3(0.0f, 0.0f, 1.0f)));
	moon->addTransformation(new TransformationRotate(3.0f, glm::vec3(0.0f, 1.0f, 0.0f), true));
	moon->addTransformation(new TransformationTranslate(glm::vec3(0.0f, 0.0f, 3.0f)));
	moon->addTransformation(new TransformationRotate(0.3f, glm::vec3(0.0f, 1.0f, 0.0f), true));
	moon->addTransformation(new TransformationTranslate(glm::vec3(0.0f, 0.0f, 1.0f)));


	DrawableObject* my_plain = new DrawableObject(plain, 6, 6, shader_phong, material_phong);
	my_plain->addTransformation(new TransformationTranslate(glm::vec3(0.0f, -0.1f, 0.0f)));
	my_plain->addTransformation(new TransformationScale(glm::vec3(35.0)));


	switch (this->choice) {
	case 1:
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
		scene->addObject(halo_sphere);
		break;
	case 4:
		scene->addObject(halo_sphere);
		break;
	case 5:
		scene->addObject(my_plain);
		std::srand(static_cast<unsigned>(std::time(nullptr)));

		for (int i = 0; i < 200; i++) {	
			float x = -35 + (std::rand() % (-35 - 35 + 1));
			float z = -35 + (std::rand() % (-35 - 35 + 1));
			float random_scale = static_cast<float>(std::rand()) / RAND_MAX;
			random_scale = 0.1f + random_scale * 1.9f;
			float random_angle = rand() % 361;
			int random_shader = std::rand() % shaders.size();

			std::vector<std::tuple<const float*, int>> my_objects;

			my_objects.push_back(std::make_tuple(tree, 92814));
			my_objects.push_back(std::make_tuple(suziSmooth, 2904));
			my_objects.push_back(std::make_tuple(bushes, 8730));
			my_objects.push_back(std::make_tuple(sphere, 2880));

			int random_object = std::rand() % my_objects.size();
			int random_material = std::rand() % materials.size();

			DrawableObject* my_object = new DrawableObject
			(std::get<0>(my_objects[random_object]), 6, std::get<1>(my_objects[random_object]), shaders[random_shader]);
			if (my_object->getShader().getShaderType() == ShaderType::PHONG) {
				my_object->material = material_phong;
			} if (my_object->getShader().getShaderType() == ShaderType::LAMBERT) {
				my_object->material = material_lambert;
			} if (my_object->getShader().getShaderType() == ShaderType::CLASSIC) {
				my_object->material = material_classic;
			} if (my_object->getShader().getShaderType() == ShaderType::CONSTANT) {
				my_object->material = materials[random_material];
			}

			my_object->addTransformation(new TransformationScale(glm::vec3(random_scale)));
			my_object->addTransformation(new TransformationRotate(random_angle, glm::vec3(0.0f, 1.0f, 0.0f), false));
			my_object->addTransformation(new TransformationTranslate(glm::vec3(x, -1.0f, z)));

			scene->addObject(my_object);
		}
		break;
	default:
		std::cout << "Invalid choice. Please enter a valid number." << std::endl;
		break;
	}

	

	for (DrawableObject* o : scene->objects) {
		o->useProg();
		camera->addObserver(&o->getShader());
		o->setMaterial();
		o->setLight(glm::vec3(0.0, 0.0, -5.0), glm::vec3(1.0, 1.0, 1.0), cameraPos);	
	}

	camera->updateCamera();
	camera->setMouseInput(this->window);

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(this->window)) {
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render all models in the scene
		for (DrawableObject* o : scene->objects) {
			o->useProg();			
			o->transform();
			o->bindArray();
			o->drawArrays();
			
		}

		camera->processInput(this->window, deltaTime);

		glfwPollEvents();
		glfwSwapBuffers(this->window);
	}
	glfwDestroyWindow(this->window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}