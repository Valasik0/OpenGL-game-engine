#include "TransformationRotate.h"

TransformationRotate::TransformationRotate(float angle, glm::vec3 axis, bool continuous) {
    this->angle = angle;
    this->axis = axis;
    this->tmp_angle = 0;
    this->continuousRotation = continuous;
}

glm::mat4 TransformationRotate::traverse() {
    if (continuousRotation) {
        this->tmp_angle += this->angle;
    }
    else {
        this->tmp_angle = this->angle;
    }
    return glm::rotate(glm::mat4(1.0f), glm::radians(this->tmp_angle), this->axis);
}