//
// Created by hal_9000 on 2025-03-18.
//

#include "pot_exceptions.h"

const char * RaiseAttemptWhileUnmatched::what()
{
    return "You can't raise the bet while there is an unmatched bet raise\n";
}

const char * ExceedMaxBetRaise::what()
{
    return "You somehow exceeded the maximum bet raise allowed\n";
}

const char * DifferentBetMatch::what()
{
    return "Your bet match differs from the last bet raise\n";
}

const char * InsufficientFunds::what()
{
    return "Your wallet isn't fat enough to match the bet raise\n";
}

const char * BetMatchAttemptInvalid::what()
{
    return "There is no bet raise to match\n";
}
const char * BetRaiseAmountExceedWallet::what()
{
    return "Your wallet isn't fat enough to make that bet raise\n";
}

const char * InsufficientFundsToMatch::what()
{
    return "You don't have the sufficient money to match that bet raise\n";
}

const char * BetRaiseAttemptWhileUnmatched::what()
{
    return "You can't raise the bet while an unmatched bet raise is present\n";
}

const char * BlindBetExceedWallet::what()
{
    return "You don't have the sufficient money to match blind bet\n";
}

const char * BetMatchByPlayerWhoRaisedIt::what()
{
    return "A player has tried matching a bet that he raised\n";
}

