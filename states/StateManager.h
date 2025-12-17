#pragma once
#include "State.h"
#include <memory>
#include <stack>
#include <SFML/System/Clock.hpp>

class StateManager {
private:
    std::stack<std::unique_ptr<State>> states;
    std::unique_ptr<State> nextState;
    int popCount = 0;
    sf::Clock inputClock; // For input buffering
    float inputBuffer = 0.2f;

public:
    ~StateManager() = default;
    void pushState(std::unique_ptr<State> state);
    void popState(int count = 1);
    State* currentState();
    void processStateChanges();
    bool canProcessInput();
    void resetInputBuffer();
};