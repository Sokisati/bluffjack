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
    startRound();
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

void Table::startRound()
{
    std::string inputString;

    takeBlindBets();
    dealInitialCards();

    gladosCardDrawCycle();

    humanPlayer.raiseYellowFlag();
    glados.raiseYellowFlag();

    inputString = humanActionLoop();
    takeCounterAction(inputString);

}

std::string Table::humanActionLoop()
{
    std::string inputString;
    while(true)
    {
        printLegalMovesForHuman();
        std::cin>>inputString;
        if(questionLegality(inputString))
        {
            takeInputAction(inputString);
            return inputString;
        }
        else
        {
        std::cout<<"Input invalid. Try again\n";
        }
    }

}

void Table::printLegalMovesForHuman()
{
    unsigned int maxBetRaiseAllowed = getMaxBetRaiseAllowed();
    unsigned int handSize = humanPlayer.getHandDeck().getNumberOfCards();
    bool greenFlag = (humanPlayer.getFlagState()==green);


    if(maxBetRaiseAllowed>0 && !pot.getUnmatchedBetState())
    {
        std::cout<<"Max. bet raise allowed is: "<<maxBetRaiseAllowed<<". ";
    }
    //TODO: 5 shall be easily changable
    if(handSize<5)
    {
        std::cout<<"You can draw a card. ";
    }
    if(!greenFlag)
    {
        std::cout<<"You can raise green flag. ";
    }
    std::cout<<"You can fold.\n";


}

bool Table::questionLegality(std::string string)
{
    unsigned int maxBetRaiseAllowed = getMaxBetRaiseAllowed();
    unsigned int handSize = humanPlayer.getHandDeck().getNumberOfCards();
    bool greenFlag = (humanPlayer.getFlagState()==green);

    if(string=="draw")
    {
        return (humanPlayer.getNumberOfCardsPossesed()<5);
    }
    else if(string=="raise")
    {
        return ((!pot.getUnmatchedBetState())&&(maxBetRaiseAllowed>0));
    }
    else if(string=="flag")
    {
        return (humanPlayer.getFlagState()!=green);
    }
    else if(string=="match")
    {
        return(humanPlayer.getPlayerName()!=pot.getLastBetRaisePlayerName());
    }
    else if(string=="fold")
    {
        return true;
    }
    else
    {
        std::cout<<"Input not valid. Try again\n";
        return false;
    }
}

void Table::takeInputAction(std::string string)
{
     int inputNumber;
     if(string=="draw")
     {
         humanPlayer.drawRandomCard(gameDeck);
     }
     else if(string=="raise")
     {
         while(true)
         {
             std::cout<<"How much?\n";
             std::cin>>inputNumber;
             if(inputNumber<0)
             {
                 std::cout<<"Bet raise can't be negative\n";
             }
             else if(inputNumber>getMaxBetRaiseAllowed())
             {
                 std::cout<<"You exceeded max. bet raise allowed for this round\n";
             }
             else
             {
                 humanPlayer.raiseBet(inputNumber,pot);
                 return;
             }
         }
     }
     else if(string=="flag")
     {
         humanPlayer.raiseGreenFlag();
     }
    else if(string=="match")
    {
        humanPlayer.matchBetRaise(pot);
    }
    else if(string=="fold")
    {
        humanPlayer.raiseRedFlag();
    }
}

void Table::takeCounterAction(std::string string)
{

    if(string=="raise")
    {
     if(glados.matchBetOrNot(pot.getBetRaiseForRound(),humanPlayer.getHandDeck()))
     {
         glados.matchBetRaise(pot);
     }
     else
     {
         glados.raiseRedFlag();
     }
    }
    else if(string=="fold")
    {
        return;
    }
    else if(string=="flag"||string=="draw")
    {
        unsigned int betRaiseByGlados = glados.betRaiseOrNot(humanPlayer.getHandDeck(),glados.getKnownDeck(),maxBet);
        if(betRaiseByGlados>0)
        {
            glados.raiseBet(betRaiseByGlados,pot);
            humanPlayer.raiseYellowFlag();
        }
        else
        {
            glados.raiseGreenFlag();
        }
    }
}

void Table::compareFlagsAndTakeAction()
{

}

