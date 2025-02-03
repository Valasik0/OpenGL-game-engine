#include "Camera.h"
#include "Shader.h"

Camera::Camera(glm::vec3 eye, glm::vec3 target, glm::vec3 up, GLFWwindow* window) {
    this->eye = eye;
    this->target = target;
    this->up = up;
    this->nearClipping = 0.1f;
    this->farClipping = 200.0f;
    glfwGetFramebufferSize(window, &winWidth, &winHeight);
    this->viewMatrix = glm::lookAt(eye, target, up);
    this->projectionMatrix = glm::perspective(glm::radians(45.0f), (float)winWidth / (float)winHeight, nearClipping, farClipping);
    this->yaw = -90.0f;
    this->pitch = 0.0f;
    this->firstMouse = true;
}

void Camera::processInput(GLFWwindow* window)
{
    const float cameraSpeed = 0.1;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        eye += cameraSpeed * target;
        updateCamera();
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        eye -= cameraSpeed * target;
        updateCamera();
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        eye -= glm::normalize(glm::cross(target, up)) * cameraSpeed;
        updateCamera();
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        eye += glm::normalize(glm::cross(target, up)) * cameraSpeed;
        updateCamera();
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        eye += up * cameraSpeed;
        updateCamera();
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        eye -= up * cameraSpeed;
        updateCamera();
    }
}

void Camera::setMouseInput(GLFWwindow* window)
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    lastX = this->winWidth / 2;
    lastY = this->winHeight / 2;
}

void Camera::mouseInput(double xpos, double ypos)
{
    if (this->firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        this->firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    target = glm::normalize(direction);
    updateCamera();
}

void Camera::refreshMouse() {
    this->firstMouse = true;
}

void Camera::setWindowSize(float w, float h) {
    this->winWidth = w;
    this->winHeight = h;
}

void Camera::windowChange(float w, float h) {
    setWindowSize(w, h);
    updateProjectionMatrix();
    notify(this, ChangeType::WindowChanged);
}

void Camera::updateProjectionMatrix() {
    this->projectionMatrix = glm::perspective(glm::radians(45.f), 
        (float)this->winWidth / (float)this->winHeight, 
        this->nearClipping,
        this->farClipping);
}

void Camera::updateViewMatrix() {
    this->viewMatrix = glm::lookAt(eye, eye + target, up);
}

glm::mat4 Camera::getProjection() {
    return this->projectionMatrix;
}

glm::mat4 Camera::getView() {
    return this->viewMatrix;
}

glm::vec3 Camera::getPosition() {
    return this->eye;
}

glm::vec3 Camera::getTarget() {
    return this->target;
}

void Camera::update(void* object, ChangeType change) {}

void Camera::updateCamera() {
    updateViewMatrix();
    updateProjectionMatrix();
    notify(this, ChangeType::CameraChanged);
}