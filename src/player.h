//
// Created by hal_9000 on 2025-03-13.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "deck.h"
#include "pot.h"
#include "string"
#include "map"
#include <iomanip>

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
    unsigned int getNumberOfCardsPossesed();
    void givePseudoCard(CardType cardType);
    void openAllCards();
    void openFirstCard();
    HandDeck getHandDeck();
    HandDeck getOpenHandDeck();
    void printHand();
    void openCardSequantially();
    void matchBetRaise(Pot &pot);
    void raiseBet(unsigned int amount, Pot &pot);
    void putBlindBet(unsigned int amount, Pot &pot);
    void takeAllTheMoneyFromPot(Pot &pot);
    void printFinancialContent();
    void giveMoney(unsigned int amount);
    void updateKnownDeck(HandDeck opponentHand);
    void equaliseKnownDeck(GameDeck gameDeck);
    void printKnownDeck();
    GameDeck getKnownDeck();
    void clearHand();

    unsigned int getMoney();
    Player(std::string name,unsigned int deckMultiplier);
};

struct BotParameterPack
{
    //bar divider value shall be 2 if all we want is a simple ceil function
    const unsigned int barDivider = 2;
    const unsigned int maxBetRaise = 5;
    double getDrawProbabilityHuman(unsigned int handValue);
    const double assumalWinProbWeight = 0.3;
};

class Bot : public Player
{

    BotParameterPack botParamPack;
    unsigned int getNumberOfUnknownCards(HandDeck opponentDeck);
    HandDeck getKnownCardHand(HandDeck opponentDeck);
    std::vector<HandDeck> getCombinationHands(GameDeck knownDeck,HandDeck opponentDeck);
    std::vector<std::vector<unsigned int>> generateCombinations(unsigned int setSize, unsigned int selection);
    unsigned int calculateCombinations(int setSize, int selection);
    double calculateInitialWinningProbability(std::vector<HandDeck> handDeckVector);
    double calculateAftermathWinningProbability(GameDeck knownDeck,HandDeck opponentDeck);
    std::map<int, double> computeDistribution(HandDeck currentHand,
                                          GameDeck deck,
                                          int drawsSoFar,
                                          double cumProb);
    std::map<int, double> getOpponentProbabilities(HandDeck openHandDeck,
                                               GameDeck knownDeck);

public:
    double getComplexWinProb(HandDeck opponentHand,GameDeck knownDeck);
    double getAssumedWinProbRaw(HandDeck opponentHand,GameDeck knownDeck);
    Bot(std::string name,unsigned int deckMultiplier);
    bool matchBetOrNot(unsigned int betRaiseForRound,HandDeck opponentDeck);
    double getExpectedValue(GameDeck knownDeck,HandDeck opponentDeck);

};




#endif //PLAYER_H
