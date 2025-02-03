#include "TransformationBezier.h"

TransformationBezier::TransformationBezier(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
	this->B = glm::mat4x3(
		p0,
		p1,
		p2,
		p3);
}

glm::mat4 TransformationBezier::traverse() {
	glm::vec4 parameters = glm::vec4(t * t * t, t * t, t, 1.0f);
	glm::vec3 p = parameters * A * glm::transpose(B);

	if (t >= 1.0f || t <= 0.0f) delta *= -1;

	t += delta;
	return glm::translate(glm::mat4(1.0f), p);
}