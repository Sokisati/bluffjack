//
// Created by hal_9000 on 2025-03-31.
//

#ifndef TREE_EXCEPTIONS_H
#define TREE_EXCEPTIONS_H
#include "exception"
struct ProbabilityMapValueNotPresent: public std::exception {
    const char* what();
};
#endif //TREE_EXCEPTIONS_H
