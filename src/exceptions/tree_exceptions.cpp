//
// Created by hal_9000 on 2025-03-31.
//

#include "tree_exceptions.h"

const char * ProbabilityMapValueNotPresent::what()
{
    throw "Congrats, you broke math and logic. Somehow, value you passed doesn't have a probability value assosicated to it";
}
