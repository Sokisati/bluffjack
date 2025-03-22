//
// Created by hal_9000 on 2025-03-20.
//

#include "card_exceptions.h"

const char * CardToRemoveNotFoundInDeck::what()
{
    return "Card to remove doesn't exist in the target deck\n";
}
