#include "Scene.h"
Scene::Scene() {}

void Scene::addObject(DrawableObject* o) {
	this->objects.push_back(o);
}
