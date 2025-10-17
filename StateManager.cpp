//
// Created by Siebe Haché on 14/10/2025.
//

#include "StateManager.h"

void StateManager::pushState(std::unique_ptr<State> state) {
    nextState = std::move(state);
}
void StateManager::popState(){
    shouldPop = true;
}

State* StateManager::currentState() {
    return states.empty() ? nullptr : states.top().get();
}

void StateManager::processStateChanges() {
    if (shouldPop && !states.empty()) {
        states.pop();
        shouldPop = false;
    }
    if (nextState) {
        states.push(std::move(nextState));
    }
}