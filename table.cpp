//
// Created by hal_9000 on 2025-03-13.
//

#include "Table.h"

Table::Table(unsigned int deckMultiplier, unsigned int startingMoney) : gameDeck(deckMultiplier)
{

}

void Table::debugEnv()
{
    gameDeck.createDebugDeck();
    humanPlayer.givePseudoCard(SIX);
    humanPlayer.givePseudoCard(TEN);


    glados.givePseudoCard(TEN);
    glados.givePseudoCard(FIVE);

    humanPlayer.openFirstCard();

    glados.getExpectedValue(gameDeck,humanPlayer.getHandDeck());

}
