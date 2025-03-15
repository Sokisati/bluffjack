//
// Created by hal_9000 on 2025-03-13.
//

#ifndef POT_H
#define POT_H


class Pot
{
    int totalMoneyInsidePot = 0;
    bool uncalledBet = false;
    int unmatchedBet = 0;

public:
    void putMoneyInPot(int amount);
    void takeMoneyFromPot(int amount);

};

#endif //POT_H
