//
// Created by hal_9000 on 2025-03-13.
//

#include "pot.h"
#include "iostream"
#include "exceptions/pot_exceptions.h"


bool Pot::getUnmatchedBetState()
{
    return unmatchedBetState;
}

unsigned int Pot::getUnmatchedBetAmount()
{
    return unmatchedBet;
}

void Pot::takeBlindBet(unsigned int blindBetAmount)
{
    this->blindBetPile+=blindBetAmount;
}

void Pot::takeBetRaise(unsigned int amount)
{
    if(unmatchedBetState)
    {
    throw BetRaiseAttemptWhileUnmatched();
    }
    if(amount>getMaxBetRaiseAllowed())
    {
        throw ExceedMaxBetRaise();
    }

    unmatchedBetState=true;
    betRaisePile+=amount;
    unmatchedBet=amount;
}

void Pot::takeBetRaiseMatch(unsigned int amount)
{
    if(amount!=unmatchedBet)
    {
        throw DifferentBetMatch();
    }
    if(!unmatchedBetState) {
        throw BetMatchAttemptInvalid();
    }

    unmatchedBetState=false;
    betRaisePile+=amount;
    unmatchedBet=0;
}

unsigned int Pot::getMaxBetRaiseAllowed()
{
    if(unmatchedBetState)
    {
        return (maxBetRaise-((betRaisePile+unmatchedBet)/2));
    }
    else
    {
       return maxBetRaise-(betRaisePile/2);
    }

}

unsigned int Pot::getAllMoney()
{
    return (blindBetPile+betRaisePile);
}

unsigned int Pot::giveAllMoneyToPlayer()
{
    unsigned int totalMoney = getAllMoney();
    blindBetPile=0;
    betRaisePile=0;
    return totalMoney;
}

void Pot::printContent()
{
    std::cout<<"Blind bet pile: "<<blindBetPile<<"\n";
    std::cout<<"Bet raise pile: "<<betRaisePile<<"\n";
    std::cout<<"Unmatched bet amount: "<<unmatchedBet<<"\n";
    std::cout<<"Unmatched bet state: "<<unmatchedBetState<<"\n";
}

Pot::Pot(unsigned int maxBetAmount)
{
    this->maxBetRaise = maxBetAmount;
}
