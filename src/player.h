//
// Created by hal_9000 on 2025-03-13.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "deck.h"
#include "pot.h"
#include "string"

class Player
{
    unsigned int money = 0;
    HandDeck handDeck;
    unsigned int numberOfCardsPossesed = 0;
    std::string name;
    GameDeck knownDeck;
    void drawCard(Card cardToDraw);
public:

    void drawImaginaryCard(Card imaginaryCard);
    void drawCardFromDeck(Card cardToDraw,GameDeck &deckToBeDrawn);
    void drawRandomCard(GameDeck &deckToBeDrawn);
    unsigned int getNumberOfCardsPossesed() const;
    void givePseudoCard(CardType cardType);
    void openAllCards();
    void openFirstCard();
    HandDeck getHandDeck();
    void printHand();
    void openCardSequantially();
    void matchBetRaise(Pot &pot);
    void raiseBet(unsigned int amount, Pot &pot);
    void putBlindBet(unsigned int amount, Pot &pot);
    void takeAllTheMoneyFromPot(Pot &pot);
    void printFinancialContent();
    void giveMoney(unsigned int amount);
    void updateKnownDeck(GameDeck originalDeck);
    void printKnownDeck();

    unsigned int getMoney();
    Player(std::string name,unsigned int deckMultiplier);
};

class Bot : public Player
{

    unsigned int getNumberOfUnknownCards(HandDeck opponentDeck);
    HandDeck getKnownCardHand(HandDeck opponentDeck);
    std::vector<HandDeck> getCombinationHands(GameDeck knownDeck,HandDeck opponentDeck);
    std::vector<std::vector<unsigned int>> generateCombinations(unsigned int setSize, unsigned int selection);
    unsigned int calculateCombinations(int setSize, int selection);
    double calculateInitialWinningProbability(std::vector<HandDeck> handDeckVector);
    double calculateAftermathWinningProbability(GameDeck knownDeck,HandDeck opponentDeck);

public:
    Bot(std::string name,unsigned int deckMultiplier);
    double getExpectedValue(GameDeck knownDeck,HandDeck opponentDeck);

};




#endif //PLAYER_H
