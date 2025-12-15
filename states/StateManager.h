//
// Created by Siebe Haché on 14/10/2025.
//

#ifndef STATEMANAGER_H
#define STATEMANAGER_H
#include "State.h"
#include <stack>

class StateManager {
private:
    std::stack<std::unique_ptr<State>> states;
    std::unique_ptr<State> nextState = nullptr;
    bool shouldPop = false;

public:
    void pushState(std::unique_ptr<State> state);

    void popState();

    State* currentState();

    void processStateChanges();
};

#endif // STATEMANAGER_H
