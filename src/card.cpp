//
// Created by hal_9000 on 2025-03-12.
//

#include "card.h"
#include "iostream"


Card::Card(CardSuit cardSuit, CardType cardType)
{
this->cardSuit=cardSuit;
this->cardType=cardType;
}

unsigned int Card::getCardValue()
{
    if(cardType==Q ||cardType==K || cardType==J)
    {
    return 10;
    }
    else if(cardType==A)
    {
    return 11;
    }
    else
    {
    return cardType;
    }
}

void Card::flipCard()
{
    if(this->cardState==down)
    {
        this->cardState=up;
    }
    else
    {
        this->cardState=down;
    }
}

bool Card::operator==(Card cardToCompare)
{
   if(cardToCompare.getCardSuit()==this->cardSuit &&
       cardToCompare.getCardType()==this->cardType)
   {
       return true;
   }
   else
   {
       return false;
   }
}

CardSuit Card::getCardSuit()
{
    return this->cardSuit;
}

CardType Card::getCardType()
{
    return this->cardType;
}

CardState Card::getCardState()
{
    return this->cardState;
}

void Card::printCard()
{

    if(cardState==up)
    {
        std::cout<<"up: ";
    }
    else
    {
    std::cout<<"down: ";
    }

    if(cardType==K)
    {
    std::cout<<"K ";
    }
    else if(cardType==Q)
    {
     std::cout<<"Q ";
    }
    else if(cardType==A)
    {
        std::cout<<"A ";
    }
    else if(cardType==J)
    {
        std::cout<<"J ";
    }
    else
    {
        std::cout<<cardType;
    }

    std::cout<<" of";

    if(cardSuit==SPADES)
    {
        std::cout<<" spades"<<"\n";
    }
    else if(cardSuit==HEARTS)
    {
        std::cout<<" hearts"<<"\n";
    }
    else if(cardSuit==DIAMONDS)
    {
        std::cout<<" diamonds"<<"\n";
    }
    else if(cardSuit==CLUBS)
    {
        std::cout<<" clubs"<<"\n";
    }

}

void Card::openCard()
{
    this->cardState = up;
}

void Card::closeCard()
{
    this->cardState = down;
}

