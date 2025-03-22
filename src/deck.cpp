//
// Created by hal_9000 on 2025-03-12.
//

#include "deck.h"
#include "iostream"
#include "exceptions/card_exceptions.h"

void Deck::addCard(Card cardToAdd)
{
    deckVector.push_back(cardToAdd);
}

void Deck::removeCard(Card cardToRemove)
{

    for(int i=0; i<deckVector.size(); i++)
    {
        if(deckVector[i]==cardToRemove)
        {
            deckVector.erase(deckVector.begin()+i);
            return;
        }
    }
    throw CardToRemoveNotFoundInDeck();
}

unsigned int Deck::getNumberOfCards()
{
    return deckVector.size();
}

Card Deck::returnCardAtIndex(unsigned int index)
{
    return deckVector[index];
}

void Deck::printDeck()
{
    for(Card card : deckVector)
    {
        card.printCard();
    }
    std::cout<<"\n";
}

std::vector<Card> Deck::getDeckVector()
{
    return deckVector;
}

void Deck::clearDeck()
{
    deckVector.clear();
}

void Deck::openFirstCard()
{
    deckVector[0].openCard();
}

void Deck::removeCardAtIndex(unsigned int index)
{
    this->deckVector.erase(deckVector.begin()+index);
}

void GameDeck::createAndAddCard(CardSuit cardSuit, CardType cardType)
{
    Card tempCard(cardSuit,cardType);
    addCard(tempCard);
}

void GameDeck::fillCards()
{
    for(int i=0; i<deckMultiplier; i++)
    {
        createAndAddCard(SPADES,TWO);
        createAndAddCard(SPADES,THREE);
        createAndAddCard(SPADES,FOUR);
        createAndAddCard(SPADES,FIVE);
        createAndAddCard(SPADES,SIX);
        createAndAddCard(SPADES,SEVEN);
        createAndAddCard(SPADES,EIGHT);
        createAndAddCard(SPADES,NINE);
        createAndAddCard(SPADES,TEN);
        createAndAddCard(SPADES,A);
        createAndAddCard(SPADES,K);
        createAndAddCard(SPADES,J);
        createAndAddCard(SPADES,Q);

        createAndAddCard(HEARTS,TWO);
        createAndAddCard(HEARTS,THREE);
        createAndAddCard(HEARTS,FOUR);
        createAndAddCard(HEARTS,FIVE);
        createAndAddCard(HEARTS,SIX);
        createAndAddCard(HEARTS,SEVEN);
        createAndAddCard(HEARTS,EIGHT);
        createAndAddCard(HEARTS,NINE);
        createAndAddCard(HEARTS,TEN);
        createAndAddCard(HEARTS,A);
        createAndAddCard(HEARTS,K);
        createAndAddCard(HEARTS,J);
        createAndAddCard(HEARTS,Q);

        createAndAddCard(DIAMONDS,TWO);
        createAndAddCard(DIAMONDS,THREE);
        createAndAddCard(DIAMONDS,FOUR);
        createAndAddCard(DIAMONDS,FIVE);
        createAndAddCard(DIAMONDS,SIX);
        createAndAddCard(DIAMONDS,SEVEN);
        createAndAddCard(DIAMONDS,EIGHT);
        createAndAddCard(DIAMONDS,NINE);
        createAndAddCard(DIAMONDS,TEN);
        createAndAddCard(DIAMONDS,A);
        createAndAddCard(DIAMONDS,K);
        createAndAddCard(DIAMONDS,J);
        createAndAddCard(DIAMONDS,Q);

        createAndAddCard(CLUBS,TWO);
        createAndAddCard(CLUBS,THREE);
        createAndAddCard(CLUBS,FOUR);
        createAndAddCard(CLUBS,FIVE);
        createAndAddCard(CLUBS,SIX);
        createAndAddCard(CLUBS,SEVEN);
        createAndAddCard(CLUBS,EIGHT);
        createAndAddCard(CLUBS,NINE);
        createAndAddCard(CLUBS,TEN);
        createAndAddCard(CLUBS,A);
        createAndAddCard(CLUBS,K);
        createAndAddCard(CLUBS,J);
        createAndAddCard(CLUBS,Q);
    }
}

void GameDeck::addPseudoCard(CardType cardType)
{
    Card tempCard(SPADES,cardType);
    addCard(tempCard);
}

void GameDeck::createDebugDeck()
{
    clearDeck();
    addPseudoCard(TWO);
    addPseudoCard(SIX);
    addPseudoCard(NINE);
    addPseudoCard(TEN);

}

GameDeck::GameDeck(unsigned int deckMultiplier)
{
    rng.seed(std::random_device()());
    this->deckMultiplier = deckMultiplier;
    fillCards();
}

Card GameDeck::getRandomCard()
{
    Card tempCard(SPADES,TWO);
    std::uniform_int_distribution<unsigned int> distribution(0, getDeckVector().size() - 1);
    unsigned int randomIndex = distribution(rng);
    tempCard = getDeckVector()[randomIndex];
    removeCardAtIndex(randomIndex);
    return tempCard;

}

unsigned int HandDeck::getTotalValue()
{
    unsigned int totalValue = 0;
    std::vector<Card> tempDeckVector = getDeckVector();

    for(Card card : tempDeckVector)
    {
        totalValue += card.getCardValue();
    }

    return totalValue;

}

unsigned int HandDeck::getNumberOfAcesInHand()
{
    std::vector<Card> tempDeckVector = getDeckVector();
    unsigned int numberOfAces = 0;
    for(Card card : tempDeckVector)
    {
        if(card.getCardType()==A)
        {
            numberOfAces++;
        }
    }
    return numberOfAces;
}

unsigned int HandDeck::getGameValue()
{
    unsigned int numberOfAces = getNumberOfAcesInHand();
    unsigned int totalValue = getTotalValue();

    if(totalValue>21)
    {
    for(; numberOfAces>0; numberOfAces--)
    {
        totalValue -= 10;
        if(totalValue<=21)
        {
        return totalValue;
        }
    }
        return 0;
    }
    else
    {
    return totalValue;
    }

}

HandDeck HandDeck::operator+(HandDeck handDeckToAdd)
{
    HandDeck sumDeck;

    for(Card card : getDeckVector())
    {
    sumDeck.addCard(card);
    }
    for(Card card : handDeckToAdd.getDeckVector())
    {
        sumDeck.addCard(card);
    }

    return sumDeck;
}

void Deck::openCardSequantially()
{
    //TODO: THIS IS UGLY
    for(int i=0; i<getNumberOfCards(); i++)
    {
        if(returnCardAtIndex(i).getCardState()==down)
        {
            deckVector[i].openCard();
            break;
        }
    }

}


