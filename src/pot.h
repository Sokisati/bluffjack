//
// Created by hal_9000 on 2025-03-13.
//

#ifndef POT_H
#define POT_H
#include "string"
class Pot
{

    unsigned int blindBetPile = 0;
    unsigned int betRaisePile = 0;
    unsigned int unmatchedBet = 0;
    unsigned int maxBetRaise = 0;
    bool unmatchedBetState = false;
    std::string lastBetRaiseName;

    unsigned int getAllMoney();
public:
    bool getUnmatchedBetState();
    unsigned int getUnmatchedBetAmount();
    void takeBlindBet(unsigned int blindBetAmount);
    void takeBetRaise(unsigned int amount,std::string playerName);
    void takeBetRaiseMatch(unsigned int amount,std::string playerName);
    unsigned int getMaxBetRaiseAllowed();
    unsigned int giveAllMoneyToPlayer();
    unsigned int giveHalfPortionToPlayer();
    void printContent();
    Pot(unsigned int maxBetAmount);
    unsigned int getBetRaiseForRound();
    std::string getLastBetRaisePlayerName();

};

#endif //POT_H
