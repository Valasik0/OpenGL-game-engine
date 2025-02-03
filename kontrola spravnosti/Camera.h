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
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> 
#include "Observer.h"
#include "Subject.h"
class Shader;
class Camera : public Observer, public Subject
{
public:
    Camera(glm::vec3 eye, glm::vec3 target, glm::vec3 up, GLFWwindow* window);
    void updateViewMatrix();
    void updateCamera();
    glm::mat4 getProjection();
    glm::mat4 getView();
    glm::vec3 getPosition();
    void processInput(GLFWwindow* window, const float dt);
    void mouseInput(double xpos, double ypos);
    void setMouseInput(GLFWwindow* window);
    void windowChange(float w, float h);
    void refreshMouse();
private:
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    glm::vec3 eye;
    glm::vec3 target;
    glm::vec3 up;
    float yaw;
    float pitch;
    bool firstMouse;
    float lastX = 0;
    float lastY = 0;
    int winHeight = 0;
    int winWidth = 0;
    bool changeMade = false;
    void update(void* object, ChangeType change);
    void setWindowSize(float w, float h);
    void updateProjectionMatrix();
};
