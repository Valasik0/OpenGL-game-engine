#include "Bezier.h"

Bezier::Bezier(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
	this->B = glm::mat4x3(glm::vec3(-0.3, 0, 0),
		glm::vec3(0, 0, 0.3),
		glm::vec3(0, 0, -0.3),
		glm::vec3(0.3, 0, 0));
}

glm::vec3 Bezier::getBezierPoint() {

	glm::vec4 parameters = glm::vec4(t * t * t, t * t, t, 1.0f);
	glm::vec3 p = parameters * A * glm::transpose(B);

    return p;
}

void Bezier::updateParametr(float delta) {

	
	if (this->t > 1.0f) growing = false;
	if (this->t < 0.0f) growing = true;

	this->t = growing ? this->t + 0.005f : this->t - 0.005f;
	printf("%f,", t);
}