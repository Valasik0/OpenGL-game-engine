#include "Subject.h"

void Subject::addObserver(Observer* obs) {
    this->observers.push_back(obs);
}

void Subject::notify(void* object, ChangeType change) {
    for (int i = 0; i < observers.size(); ++i)
        observers[i]->update(object, change);
}