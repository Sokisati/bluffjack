//
// Created by hal_9000 on 2025-03-13.
//

#include "player.h"
#include "iostream"

void Player::drawCard(Card cardToDraw)
{
    handDeck.addCard(cardToDraw);
    this->numberOfCardsPossesed++;
}

void Player::drawImaginaryCard(Card imaginaryCard)
{
    drawCard(imaginaryCard);
}

void Player::drawCardFromDeck(Card cardToDraw,GameDeck &deckToBeDrawn)
{
    deckToBeDrawn.removeCard(cardToDraw);
    drawCard(cardToDraw);
}

unsigned int Player::getNumberOfCardsPossesed() const
{
    return this->numberOfCardsPossesed;
}

void Player::givePseudoCard(CardType cardType)
{
    Card tempCard(SPADES,cardType);
    drawImaginaryCard(tempCard);
}

void Player::openAllCards()
{
    for(Card card : handDeck.getDeckVector())
    {
        card.openCard();
    }
}

void Player::openFirstCard()
{
    handDeck.openFirstCard();
}

HandDeck Player::getHandDeck()
{
    return handDeck;
}

unsigned int Bot::calculateCombinations(int setSize, int selection) {
    if (selection > setSize) return 0;
    unsigned int result = 1;
    for (int i = 0; i < selection; ++i) {
        result *= (setSize - i);
        result /= (i + 1);
    }
    return result;
}

double Bot::calculateInitialWinningProbability(std::vector<HandDeck> handDeckVector)
{
    double winCounter = 0;
    double tieCounter = 0;
    double loseCounter = 0;

    unsigned int ownHandValue = getHandDeck().getGameValue();
    for(HandDeck handDeck : handDeckVector)
    {
        if(ownHandValue>handDeck.getGameValue())
        {
            winCounter++;
        }
        else if(ownHandValue==handDeck.getGameValue())
        {
            tieCounter++;
        }
        else
        {
            loseCounter++;
        }
    }

    winCounter += (tieCounter/2);
    return (winCounter/(handDeckVector.size()));
}

double Bot::calculateAftermathWinningProbability(GameDeck knownDeck,
    HandDeck opponentDeck)
{

    HandDeck originalOpponentKnownCardHand = getKnownCardHand(opponentDeck);
    HandDeck opponentKnownCardHand;

    unsigned int tempGameValue = 0;
    unsigned int tempGameValueOpponent = 0;
    double aftermathWinProbablity = 0;
    double instanceWinCounter = 0;

    unsigned int numberOfUnknownCards = getNumberOfUnknownCards(opponentDeck);
    GameDeck originalDeck = knownDeck;
    HandDeck tempHandDeck;

    unsigned int numberOfPossibleCombinations = calculateCombinations(
        knownDeck.getNumberOfCards()-1,numberOfUnknownCards);

    std::vector<std::vector<unsigned int>> indexVector = generateCombinations(
    knownDeck.getNumberOfCards()-1,numberOfUnknownCards);

    for(int i=0; i<knownDeck.getNumberOfCards(); i++)
    {
        opponentKnownCardHand = getKnownCardHand(opponentDeck);
        tempHandDeck = getHandDeck();
        tempHandDeck.addCard(knownDeck.returnCardAtIndex(i));
        tempGameValue = tempHandDeck.getGameValue();
        knownDeck.removeCardAtIndex(i);

        for(int j=0; j<numberOfPossibleCombinations; j++)
        {
            for(int k=0; k<numberOfUnknownCards; k++)
            {
                opponentKnownCardHand.addCard(knownDeck.returnCardAtIndex(indexVector[j][k]));
            }
            tempGameValueOpponent = opponentKnownCardHand.getGameValue();
            if(tempGameValue>tempGameValueOpponent)
            {
            instanceWinCounter+=1;
            }
            else if(tempGameValue==tempGameValueOpponent)
            {
            instanceWinCounter+=0.5;
            }
            opponentKnownCardHand = originalOpponentKnownCardHand;
        }
        instanceWinCounter/=numberOfPossibleCombinations;
        aftermathWinProbablity+=(instanceWinCounter)/originalDeck.getNumberOfCards();

        instanceWinCounter = 0;

        knownDeck = originalDeck;
    }

    return aftermathWinProbablity;
}

double Bot::getExpectedValue(GameDeck knownDeck, HandDeck opponentDeck)
{

    double expectedValue = 0;
    double aftermathWinProbability = 0;

    std::vector<HandDeck> combinationHands = getCombinationHands(knownDeck,
        opponentDeck);
    double initialWinProbability = calculateInitialWinningProbability(combinationHands);


    for(HandDeck handDeck : combinationHands)
    {
        aftermathWinProbability = calculateAftermathWinningProbability(knownDeck,opponentDeck);;
        expectedValue += (aftermathWinProbability-initialWinProbability);
    }

    std::cout<<expectedValue<<"\n";
    return expectedValue;
}

std::vector<std::vector<unsigned int>> Bot::generateCombinations(unsigned int setSize, unsigned int selection) {
    std::vector<std::vector<unsigned int>> result;
    std::vector<unsigned int> combination(selection);

    for (unsigned int i = 0; i < selection; ++i) {
        combination[i] = i;
    }

    while (true) {
        result.push_back(combination);

        int i;
        for (i = selection - 1; i >= 0 && combination[i] == setSize - selection + i; --i);

        if (i < 0) break;

        ++combination[i];
        for (unsigned int j = i + 1; j < selection; ++j)
        {
            combination[j] = combination[j - 1] + 1;
        }
    }

    return result;
}

unsigned int Bot::getNumberOfUnknownCards(HandDeck opponentDeck)
{
    unsigned int numberOfUnknownCards = 0;

    for(Card card : opponentDeck.getDeckVector())
    {
        if(card.getCardState()==up)
        {
        numberOfUnknownCards++;
        }
    }

    return numberOfUnknownCards;
}

HandDeck Bot::getKnownCardHand(HandDeck opponentDeck)
{
    HandDeck tempDeck;
    for(Card card : opponentDeck.getDeckVector())
    {
        if(card.getCardState()==up)
        {
            tempDeck.addCard(card);
        }
    }
    return tempDeck;
}

std::vector<HandDeck> Bot::getCombinationHands(GameDeck knownDeck,HandDeck opponentDeck)
{

    unsigned int numberOfUnknownCards = getNumberOfUnknownCards(opponentDeck);
    std::vector<std::vector<unsigned int>> indexVector = generateCombinations(
    knownDeck.getNumberOfCards(),numberOfUnknownCards);
    HandDeck knownCardHand = getKnownCardHand(opponentDeck);


    std::vector<HandDeck> combinationVector;
    HandDeck tempDeck;

    unsigned int numberOfPossibleCombinations = calculateCombinations(
        knownDeck.getNumberOfCards(),numberOfUnknownCards);


    for(int i=0; i<numberOfPossibleCombinations; i++)
    {
        tempDeck = tempDeck + knownCardHand;
        for(int j=0; j<numberOfUnknownCards; j++)
        {
            tempDeck.addCard(knownDeck.returnCardAtIndex(indexVector[i][j]));
        }
        combinationVector.push_back(tempDeck);
        tempDeck.clearDeck();
    }

    return combinationVector;
}

