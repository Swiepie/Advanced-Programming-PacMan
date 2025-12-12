//
// Created by siebe on 12/12/2025.
//

#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <memory>
#include "../renderer/Observer.h"
#include <algorithm>

class Subject {
private:
	std::vector<Observer*> observers;
	Observer* primaryObserver = nullptr; // Voor de view

public:
	virtual ~Subject() = default;

	void attach(Observer* observer) {
		observers.push_back(observer);
		// Eerste observer is de view
		if (!primaryObserver) {
			primaryObserver = observer;
		}
	}

	void detach(Observer* observer) {
		observers.erase(
			std::remove(observers.begin(), observers.end(), observer),
			observers.end()
		);
		if (primaryObserver == observer) {
			primaryObserver = nullptr;
		}
	}

	void notify() {
		for (auto* observer : observers) {
			if (observer) {
				observer->update();
			}
		}
	}

	// Direct access to view
	Observer* getObserver() const {
		return primaryObserver;
	}
};




#endif //SUBJECT_H
