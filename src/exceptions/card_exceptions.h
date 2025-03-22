//
// Created by hal_9000 on 2025-03-20.
//

#ifndef CARD_EXCEPTIONS_H
#define CARD_EXCEPTIONS_H
#include "exception"
struct CardToRemoveNotFoundInDeck: public std::exception {
    const char* what();
};
#endif //CARD_EXCEPTIONS_H
