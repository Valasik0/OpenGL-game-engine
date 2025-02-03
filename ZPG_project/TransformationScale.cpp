#include "TransformationScale.h"

TransformationScale::TransformationScale(glm::vec3 values) {
	this->values = values;
}

glm::mat4 TransformationScale::traverse() {
	return glm::scale(glm::mat4(1.0f), this->values);
}