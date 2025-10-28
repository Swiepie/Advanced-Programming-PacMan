//
// Created by Siebe Haché on 14/10/2025.
//

#include "StateManager.h"

void StateManager::pushState(std::unique_ptr<State> state) {
    // Call onExit() for the current active state (if any)
    if (!states.empty())
        states.top()->onExit();

    // Schedule the new state
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
        // Call onExit() before removing
        states.top()->onExit();
        states.pop();
        shouldPop = false;

        // If there’s now a state underneath, it becomes active again
        if (!states.empty())
            states.top()->onEnter();
    }

    if (nextState) {
        // Actually push the new state now
        states.push(std::move(nextState));

        // Call onEnter() for the new top state
        states.top()->onEnter();
        nextState.reset(); // clear pending state
    }
}