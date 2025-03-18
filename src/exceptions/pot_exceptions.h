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

struct InsufficientFunds: public public std::exception {
    const char* what();
};
struct BetMatchAttemptInvalid: public public std::exception {
    const char* what();
};
struct BetRaiseAmountExceedWallet: public public std::exception {
    const char* what();
};
#endif //POT_EXCEPTIONS_H
