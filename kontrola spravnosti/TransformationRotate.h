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
#include "Transformation.h"
class TransformationRotate : public Transformation {
public:
    TransformationRotate(float angle, glm::vec3 axis, bool continuous);

    glm::mat4 traverse();

private:
    float angle;
    glm::vec3 axis;
    float tmp_angle;
    bool continuousRotation;
};

