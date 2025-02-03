#include "Composite.h"


void Composite::add(Transformation* t) {
	this->children.push_back(t);
}

glm::mat4 Composite::traverse() {
	glm::mat4 M = glm::mat4(1.0f);
	for (int i = 0; i < children.size(); i++) {
		M = children[i]->traverse() * M;
	}	
	return M;
}