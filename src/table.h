//
// Created by hal_9000 on 2025-03-13.
//

#ifndef TABLE_H
#define TABLE_H

#include "pot.h"
#include "player.h"
#include "exceptions/table_exceptions.h"


class Table
{
    Pot pot;
    Player humanPlayer;
    Bot glados;
    GameDeck gameDeck;
    unsigned int blindBet;
    unsigned int maxBet;
    unsigned int startingMoney;
    unsigned int initialCardSize = 2;
    unsigned int initialOpenCardSize = 1;
    bool endOfRound = false;

public:
    Table(unsigned int deckMultiplier, unsigned int startingMoney,
    float blindBetRatio, float maxBetRatio);
    void debugEnv();
    unsigned int getBlindBet();
    unsigned int getMaxBet();
    void dealInitialCards();
    unsigned int getPoorestWallet();
    void takeBlindBets();
    void gladosCardDrawCycle();
    void startGame();
    unsigned int getMaxBetRaiseAllowed();
    void startRound();
    std::string humanActionLoop();
    void printLegalMovesForHuman();
    bool questionLegality(const std::string &string);
    void takeInputAction(const std::string &string);
    void takeCounterAction(const std::string &string);
    void compareFlagsAndTakeAction();
    void endRound();
    std::string determineWinner();
    void winAction(std::string winnerName);
    void printPlayersContent();
    void commenceARound();
    void commenceAGame();
    bool bothPlayersCanPlay();
};


#endif //TABLE_H
