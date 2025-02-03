#pragma once
#include "Observer.h"
#include "vector"
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> 

class Subject
{
    glm::mat4 mat;
    std::vector<Observer*> observers;
    public:
        void addObserver(Observer* obs); 
        void notify(void* object, ChangeType change);
};

