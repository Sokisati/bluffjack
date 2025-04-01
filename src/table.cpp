//
// Created by hal_9000 on 2025-03-13.
//

#include "Table.h"


Table::Table(unsigned int deckMultiplier, unsigned int startingMoney,
    float blindBetRatio, float maxBetRatio): gameDeck(deckMultiplier),
pot(static_cast<float>(startingMoney)*maxBetRatio),humanPlayer("human",deckMultiplier),
glados("glados",deckMultiplier)
{
    this->startingMoney = startingMoney;
this->blindBet = static_cast<float>(startingMoney)*blindBetRatio;
this->maxBet = static_cast<float>(startingMoney)*maxBetRatio;


    glados.giveMoney(startingMoney);
    humanPlayer.giveMoney(startingMoney);

}

void Table::debugEnv()
{

    humanPlayer.givePseudoCard(TEN);
    humanPlayer.givePseudoCard(TWO);
    humanPlayer.openCardSequantially();
    glados.givePseudoCard(TEN);
    glados.givePseudoCard(SEVEN);

    GameDeck knownDeck(1);
    knownDeck.createDebugDeck();


    std::cout<<glados.getComplexWinProb(humanPlayer.getHandDeck(),knownDeck);


}

unsigned int Table::getBlindBet()
{
    return this->blindBet;
}

unsigned int Table::getMaxBet()
{
    return this->maxBet;
}

void Table::dealInitialCards()
{
    for(int i=0; i<initialCardSize; i++)
    {
        humanPlayer.drawRandomCard(gameDeck);
        glados.drawRandomCard(gameDeck);
    }
    for(int i=0; i<openCardSize; i++)
    {
        humanPlayer.openCardSequantially();
        glados.openCardSequantially();
    }


}


unsigned int Table::getPoorestWallet()
{
    return std::min(glados.getMoney(), humanPlayer.getMoney());
}

void Table::takeBlindBets()
{
    humanPlayer.putBlindBet(blindBet,pot);
    glados.putBlindBet(blindBet,pot);
}

void Table::gladosCardDrawCycle()
{
    double expectedValue = glados.getExpectedValue(glados.getKnownDeck(),humanPlayer.getHandDeck());

    while(expectedValue>0)
    {
        glados.drawRandomCard(gameDeck);
        expectedValue = glados.getExpectedValue(glados.getKnownDeck(),humanPlayer.getHandDeck());
    }
}

void Table::startGame()
{
    while(glados.getMoney()>blindBet&&humanPlayer.getMoney()>blindBet)
    {
        dealInitialCards();
        takeBlindBets();
        gladosCardDrawCycle();

    }
}

unsigned int Table::getMaxBetRaiseAllowed()
{
    return std::min(getPoorestWallet(),pot.getMaxBetRaiseAllowed());
}


