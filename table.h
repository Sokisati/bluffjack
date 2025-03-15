//
// Created by hal_9000 on 2025-03-13.
//

#ifndef TABLE_H
#define TABLE_H

#include "pot.h"
#include "player.h"


class Table
{
    Pot pot;
    Player humanPlayer;
    Bot glados;
    GameDeck gameDeck;

public:
    Table(unsigned int deckMultiplier, unsigned int startingMoney);
    void debugEnv();


};


#endif //TABLE_H
