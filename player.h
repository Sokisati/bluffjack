//
// Created by hal_9000 on 2025-03-13.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "deck.h"
#include "string"

class Player
{
    int money = 0;
    int moneyInsidePot = 0;
    HandDeck handDeck;
    unsigned int numberOfCardsPossesed = 0;

    void drawCard(Card cardToDraw);
public:

    void drawImaginaryCard(Card imaginaryCard);
    void drawCardFromDeck(Card cardToDraw,GameDeck &deckToBeDrawn);
    unsigned int getNumberOfCardsPossesed() const;
    void givePseudoCard(CardType cardType);
    void openAllCards();
    void openFirstCard();
    HandDeck getHandDeck();
};

class Bot : public Player
{

    unsigned int getNumberOfUnknownCards(HandDeck opponentDeck);
    HandDeck getKnownCardHand(HandDeck opponentDeck);
    std::vector<HandDeck> getCombinationHands(GameDeck knownDeck,HandDeck opponentDeck);
    std::vector<std::vector<unsigned int>> generateCombinations(unsigned int setSize, unsigned int selection);
    unsigned int calculateCombinations(int setSize, int selection);
    double calculateInitialWinningProbability(std::vector<HandDeck> handDeckVector);
    double calculateAftermathWinningProbability(GameDeck knownDeck,
    HandDeck opponentDeck);

public:

    double getExpectedValue(GameDeck knownDeck, HandDeck opponentDeck);



};




#endif //PLAYER_H
