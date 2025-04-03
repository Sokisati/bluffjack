//
// Created by hal_9000 on 2025-04-03.
//

#include "table_exceptions.h"

const char * TwoRedFlags::what()
{
    return "Somehow, both players raised red flag.\n";
}

const char * InvalidWinnerName::what()
{
    return "Invalid winner name\n";
}
