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

void StateManager::popState(int count) {
    // Accumulate the number of states to pop
    popCount += count;
}

State* StateManager::currentState() { return states.empty() ? nullptr : states.top().get(); }

void StateManager::processStateChanges() {
    // Pop the requested number of states
    while (popCount > 0 && !states.empty()) {
        // Call onExit() before removing
        states.top()->onExit();
        states.pop();
        popCount--;
    }

    // Reset popCount in case we ran out of states
    popCount = 0;

    // If there's a pending state to push
    if (nextState) {
        // Actually push the new state now
        states.push(std::move(nextState));

        // Call onEnter() for the new top state
        states.top()->onEnter();
        nextState.reset(); // clear pending state

        // Reset input buffer when state changes
        resetInputBuffer();
    }
}

bool StateManager::canProcessInput() { return inputClock.getElapsedTime().asSeconds() >= inputBuffer; }

void StateManager::resetInputBuffer() { inputClock.restart(); }