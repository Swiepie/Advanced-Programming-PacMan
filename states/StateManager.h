/**
 * @file StateManager.h
 * @brief Definieert de StateManager klasse voor game state beheer
 * @author Siebe Haché
 * @date 28/10/2025
 */

#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "State.h"
#include <SFML/System/Clock.hpp>
#include <memory>
#include <stack>

/**
 * @class StateManager
 * @brief Beheert de stack van game states en state transities
 *
 * Implementeert een stack-gebaseerd state management systeem voor het spel.
 * Ondersteunt push/pop operaties voor state transities en bevat input buffering
 * om ongewenste dubbele inputs te voorkomen. De actieve state staat bovenaan de stack.
 */
class StateManager {
private:
    std::stack<std::unique_ptr<State>> states; ///< Stack van game states
    std::unique_ptr<State> nextState;          ///< Volgende state voor vertraagde transitie
    int popCount = 0;                          ///< Aantal states om te verwijderen
    sf::Clock inputClock;                      ///< Klok voor input buffering timing
    float inputBuffer = 0.2f;                  ///< Input buffer duur in seconden

public:
    /**
     * @brief Destructor voor StateManager
     */
    ~StateManager() = default;

    /**
     * @brief Voegt een nieuwe state toe aan de stack
     * @param state Unieke pointer naar de toe te voegen state
     *
     * Plaatst een nieuwe state bovenaan de stack. De nieuwe state wordt
     * actief en de vorige state blijft op de stack voor later gebruik.
     */
    void pushState(std::unique_ptr<State> state);

    /**
     * @brief Verwijdert states van de stack
     * @param count Aantal states om te verwijderen (standaard 1)
     *
     * Plant het verwijderen van één of meerdere states van de stack.
     * De daadwerkelijke verwijdering gebeurt in processStateChanges().
     */
    void popState(int count = 1);

    /**
     * @brief Geeft een pointer naar de huidige actieve state
     * @return Pointer naar de bovenste state op de stack, of nullptr als leeg
     *
     * Retourneert de state bovenaan de stack zonder deze te verwijderen.
     */
    State* currentState();

    /**
     * @brief Verwerkt uitgestelde state veranderingen
     *
     * Past alle uitgestelde push en pop operaties toe op de state stack.
     * Moet aangeroepen worden aan het einde van elke frame om state transities
     * veilig door te voeren en onEnter/onExit callbacks aan te roepen.
     */
    void processStateChanges();

    /**
     * @brief Controleert of input verwerkt mag worden
     * @return true als de input buffer tijd verstreken is, anders false
     *
     * Voorkomt dat inputs te snel na elkaar verwerkt worden door een
     * minimale tijd tussen inputs af te dwingen.
     */
    bool canProcessInput();

    /**
     * @brief Reset de input buffer timer
     *
     * Start de input buffer klok opnieuw om een nieuwe buffer periode
     * in te stellen. Moet aangeroepen worden na elke verwerkte input.
     */
    void resetInputBuffer();
};

#endif // STATEMANAGER_H
