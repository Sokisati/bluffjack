//
// Created by hal_9000 on 2025-03-18.
//

#ifndef POT_EXCEPTIONS_H
#define POT_EXCEPTIONS_H

#include "exception"
struct RaiseAttemptWhileUnmatched: public std::exception {
    const char* what();
};

struct ExceedMaxBetRaise: public std::exception {
    const char* what();
};
struct DifferentBetMatch: public std::exception {
    const char* what();
};

struct InsufficientFunds: public std::exception {
    const char* what();
};
struct BetMatchAttemptInvalid: public std::exception {
    const char* what();
};
struct BetRaiseAmountExceedWallet: public std::exception {
    const char* what();
};
struct InsufficientFundsToMatch: public std::exception {
    const char* what();
};
struct BetRaiseAttemptWhileUnmatched: public std::exception {
    const char* what();
};
struct BlindBetExceedWallet: public std::exception {
    const char* what();
};
struct BetMatchByPlayerWhoRaisedIt: public std::exception {
    const char* what();
};


#endif //POT_EXCEPTIONS_H
