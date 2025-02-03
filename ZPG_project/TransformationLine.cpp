#include "TransformationLine.h"

TransformationLine::TransformationLine(glm::vec3 A, glm::vec3 B) {
	this->A = A;
	this->B = B;
}

glm::mat4 TransformationLine::traverse() {
	glm::vec3 p = A + (B - A) * t;
	if (t >= 1.0f || t <= 0.0f) delta *= -1;

	t += delta;
	return glm::translate(glm::mat4(1.0f), p);
}