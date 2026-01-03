#include "Subject.h"

void Subject::attach(Observer* obs) {
    observer = obs;
}

void Subject::detach() {
    observer = nullptr;
}

void Subject::notify() {
    if (observer) {
        observer->update();
    }
}

Observer* Subject::getObserver() const {
    return observer;
}
