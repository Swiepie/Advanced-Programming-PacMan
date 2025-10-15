//
// Created by Siebe Haché on 14/10/2025.
//

#ifndef STATEMANAGER_H
#define STATEMANAGER_H
#include <stack>
#include "State.h"

class StateManager {
private:
    std::stack<std::unique_ptr<State>> states;
    std::unique_ptr<State> nextState = nullptr;
    bool shouldPop = false;

public:
    void pushState(std::unique_ptr<State> state) {
        nextState = std::move(state);
    }

    void popState() {
        shouldPop = true;
    }

    State* currentState() {
        return states.empty() ? nullptr : states.top().get();
    }

    void processStateChanges() {
        if (shouldPop && !states.empty()) {
            states.pop();
            shouldPop = false;
        }

        if (nextState) {
            states.push(std::move(nextState));
        }
    }
};



#endif //STATEMANAGER_H
