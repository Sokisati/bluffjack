//
// Created by hal_9000 on 2025-04-03.
//

#ifndef TABLE_EXCEPTIONS_H
#define TABLE_EXCEPTIONS_H
#include "exception"
struct TwoRedFlags: public std::exception {
    const char* what();
};

struct InvalidWinnerName: public std::exception {
    const char* what();
};
#endif //TABLE_EXCEPTIONS_H
