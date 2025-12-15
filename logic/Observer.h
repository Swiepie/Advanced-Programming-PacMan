//
// Created by siebe on 12/12/2025.
//

#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
public:
    virtual void update() = 0; // Bestaande methode
    virtual ~Observer() = default;
    virtual void update(float time) = 0;
};

#endif // OBSERVER_H
