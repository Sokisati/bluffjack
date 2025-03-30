//
// Created by hal_9000 on 2025-03-13.
//

#ifndef POT_H
#define POT_H

class Pot
{

    unsigned int blindBetPile = 0;
    unsigned int betRaisePile = 0;
    unsigned int unmatchedBet = 0;
    unsigned int maxBetRaise = 0;
    bool unmatchedBetState = false;

    unsigned int getAllMoney();
public:
    bool getUnmatchedBetState();
    unsigned int getUnmatchedBetAmount();
    void takeBlindBet(unsigned int blindBetAmount);
    void takeBetRaise(unsigned int amount);
    void takeBetRaiseMatch(unsigned int amount);
    unsigned int getMaxBetRaiseAllowed();
    unsigned int giveAllMoneyToPlayer();
    void printContent();
    Pot(unsigned int maxBetAmount);
    unsigned int getBetRaiseForRound();

};

#endif //POT_H
