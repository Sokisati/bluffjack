//
// Created by hal_9000 on 2025-03-12.
//

#ifndef DECK_H
#define DECK_H

#include "vector"
#include "card.h"

class Deck {

    std::vector<Card> deckVector;

public:
    void addCard(Card cardToAdd);
    void removeCard(Card cardToRemove);
    unsigned int getNumberOfCards();
    Card returnCardAtIndex(unsigned int index);
    void printDeck();
    std::vector<Card> getDeckVector();
    void clearDeck();
    void openFirstCard();
    void removeCardAtIndex(unsigned int index);
};

class GameDeck : public Deck
{
    void createAndAddCard(CardSuit cardSuit, CardType cardType);
    void fillCards();
public:
    unsigned int deckMultiplier = 1;
    void addPseudoCard(CardType cardType);
    void createDebugDeck();
    GameDeck(unsigned int deckMultiplier);

};

class HandDeck : public Deck
{

    unsigned int getTotalValue();
public:
    unsigned int getNumberOfAcesInHand();
    unsigned int getGameValue();
    HandDeck operator+(HandDeck handDeckToAdd);



};

#endif //DECK_H
