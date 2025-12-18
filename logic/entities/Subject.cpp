//
// Created by siebe on 12/12/2025.
//

#include "Subject.h"
void Subject::attach(Observer* observer) {
    observers.push_back(observer);
    // Eerste observer is de view
    if (!primaryObserver) {
        primaryObserver = observer;
    }
}
void Subject::detach(Observer* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    if (primaryObserver == observer) {
        primaryObserver = nullptr;
    }
}
void Subject::notify() {
    for (auto* observer : observers) {
        if (observer) {
            observer->update();
        }
    }
}
Observer* Subject::getObserver() const { return primaryObserver; }