//
// Created by hal_9000 on 2025-03-13.
//

#include "pot.h"


void Pot::putMoneyInPot(int amount)
{
    this->totalMoneyInsidePot+=amount;
}

void Pot::takeMoneyFromPot(int amount)
{
    this->totalMoneyInsidePot-=amount;
}
