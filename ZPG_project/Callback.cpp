#include "Callback.h"

Callback::Callback() {};

Callback& Callback::getInstance() {
	static Callback instance;  // This will create the instance once
	return instance;
}

Camera* Callback::camera = nullptr;
Scene* Callback::scene = nullptr;

void Callback::error_callback(int error, const char* description) {
	fputs(description, stderr);
}


void Callback::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Callback::window_focus_callback(GLFWwindow* window, int focused) {
	printf("window_focus_callback \n");
}

void Callback::window_iconify_callback(GLFWwindow* window, int iconified) {
	printf("window_iconify_callback \n");
}

void Callback::window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
	camera->windowChange((float)width, (float)height);
}

void Callback::cursor_callback(GLFWwindow* window, double x, double y) {
	printf("cursor_callback \n");
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		camera->mouseInput(x, y);
	}
	
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
		camera->refreshMouse();
	}
	
}

void Callback::button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
			scene->highlightObject(window);
		}
		else if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS) {
			scene->addMovementPoint(window, 'b');
		}
		else if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
			scene->addMovementPoint(window, 'l');
		}
		else {
			scene->spawnObject(window);
		}
		
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
		scene->removeObject(window);
	}
}

void Callback::initCallbacks(GLFWwindow* window, Camera* camera, Scene* scene)
{
	Callback::scene = scene;
	Callback::camera = camera;

	glfwSetKeyCallback(window, key_callback);

	glfwSetCursorPosCallback(window, cursor_callback);

	glfwSetMouseButtonCallback(window, button_callback);

	glfwSetWindowFocusCallback(window, window_focus_callback);

	glfwSetWindowIconifyCallback(window, window_iconify_callback);

	glfwSetWindowSizeCallback(window, window_size_callback);
}