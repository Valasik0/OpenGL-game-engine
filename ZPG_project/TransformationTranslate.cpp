#include "TransformationTranslate.h"

TransformationTranslate::TransformationTranslate(glm::vec3 values) {
	this->values = values;
}

glm::mat4 TransformationTranslate::traverse() {
	return glm::translate(glm::mat4(1.0f), this->values);
}