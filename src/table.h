//
// Created by hal_9000 on 2025-03-13.
//

#ifndef TABLE_H
#define TABLE_H

#include "pot.h"
#include "player.h"
#include "map"
#include "iostream"
#include <iomanip>

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
    unsigned int openCardSize = 1;

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
};


#endif //TABLE_H
