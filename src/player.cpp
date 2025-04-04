//
// Created by hal_9000 on 2025-03-13.
//

#include "player.h"
#include "exceptions/pot_exceptions.h"
#include "cmath"
#include "exceptions/tree_exceptions.h"

void Player::drawCard(Card cardToDraw)
{
    knownDeck.removeCard(cardToDraw);
    handDeck.addCard(cardToDraw);
    std::cout<<name<<" drew a card\n";
    this->numberOfCardsPossesed++;
}

void Player::drawImaginaryCard(Card imaginaryCard)
{
    //Reason why I am not calling the draw card function is that
    //drawing an imaginary card means I am debugging and I don't
    //want to deal with knownDeck
    handDeck.addCard(imaginaryCard);
    this->numberOfCardsPossesed++;
}

void Player::drawCardFromDeck(Card cardToDraw,GameDeck &deckToBeDrawn)
{
    deckToBeDrawn.removeCard(cardToDraw);
    drawCard(cardToDraw);
}

void Player::drawRandomCard(GameDeck &deckToBeDrawn)
{
    drawCard(deckToBeDrawn.getRandomCard());
}

unsigned int Player::getNumberOfCardsPossesed()
{
    return handDeck.getNumberOfCards();
}

void Player::givePseudoCard(CardType cardType)
{
    Card tempCard(SPADES,cardType);
    drawImaginaryCard(tempCard);
}

void Player::openAllCards()
{
    handDeck.openAllCards();
}

void Player::openFirstCard()
{
    handDeck.openFirstCard();
}

HandDeck Player::getHandDeck()
{
    return handDeck;
}

HandDeck Player::getOpenHandDeck()
{
    HandDeck tempDeck;

    for(Card card : handDeck.getDeckVector())
    {
        if(card.getCardState()==up)
        {
            tempDeck.addCard(card);
        }
    }
    return tempDeck;
}

void Player::printHand()
{
    std::cout<<name<<" hand:\n";
  handDeck.printDeck();
}

void Player::openCardSequantially()
{
    handDeck.openCardSequantially();
}

void Player::matchBetRaise(Pot &pot)
{
    if(!pot.getUnmatchedBetState())
    {
        return;
    }

    unsigned int betToMatch = pot.getUnmatchedBetAmount();
    if(betToMatch>money)
    {
        throw InsufficientFundsToMatch();
    }
    std::cout<<"Player: "<<name<<" matches bet raise"<<"\n";
    pot.takeBetRaiseMatch(betToMatch,name);
    money-=betToMatch;

}

void Player::raiseBet(unsigned int amount, Pot &pot)
{

    unsigned int maxBetRaiseAllowedByPot = pot.getMaxBetRaiseAllowed();
    if(amount>maxBetRaiseAllowedByPot)
    {
        throw ExceedMaxBetRaise();
    }
    if(amount>money)
    {
        throw BetRaiseAmountExceedWallet();
    }
    if(pot.getUnmatchedBetState())
    {
     throw BetRaiseAttemptWhileUnmatched();
    }
    std::cout<<"Player: "<<name<<" raises bet by:"<<amount<<"\n";
    money-=amount;
    pot.takeBetRaise(amount,name);

}

void Player::putBlindBet(unsigned int amount, Pot &pot)
{
    if(amount>money)
    {
        throw BlindBetExceedWallet();
    }
    money-=amount;
    pot.takeBlindBet(amount);
}

void Player::takeAllTheMoneyFromPot(Pot &pot)
{
    unsigned int totalMoneyToTake = pot.giveAllMoneyToPlayer();
    money+=totalMoneyToTake;
}

void Player::printFinancialContent()
{
    std::cout<<name<<" has: "<<money<<"\n\n";
}

void Player::giveMoney(unsigned int amount)
{
    money+=amount;
}

void Player::updateKnownDeck(HandDeck opponentHand)
{
    for(Card card : opponentHand.getDeckVector())
    {
    if(card.getCardState()==up)
    {
    knownDeck.removeCard(card);
    }
    }
}

void Player::updateKnownDeckRoundEnd(HandDeck opponentHand, unsigned int initialOpenCardSize)
{
    std::vector<Card> tempVector = opponentHand.getDeckVector();
    for(unsigned int i=initialOpenCardSize; i<tempVector.size(); i++)
    {
        if(tempVector[i].getCardState()==up)
        {
            knownDeck.removeCard(tempVector[i]);
        }
    }
}

void Player::equaliseKnownDeck(GameDeck gameDeck)
{
    this->knownDeck = gameDeck;
}

void Player::printKnownDeck()
{
    knownDeck.printDeck();
}

GameDeck Player::getKnownDeck()
{
    return knownDeck;
}

void Player::clearHand()
{
    handDeck.clearDeck();
}

void Player::raiseGreenFlag()
{
    this->flag = green;
}

void Player::raiseRedFlag()
{
    std::cout<<"Player: "<<name<<" raises red flag.\n";
    this->flag = red;
}

void Player::raiseYellowFlag()
{
    flag=yellow;
}

Flag Player::getFlagState()
{
    return flag;
}

std::string Player::getPlayerName()
{
    return name;
}

unsigned int Player::getMoney()
{
    return money;
}

Player::Player(std::string name, unsigned int deckMultiplier):knownDeck(deckMultiplier)
{
    this->name=name;
}

void Player::openAllCardsInHand()
{
    handDeck.openAllCards();
}

void Player::takeHalfPortionMoneyFromPot(Pot &pot)
{
    unsigned int totalMoneyToTake = pot.giveHalfPortionToPlayer();
    money+=totalMoneyToTake;
}

void Player::printInfo()
{
    printFinancialContent();
    printHand();
    std::cout<<"Flag state: ";
    if(flag==red)
    {
        std::cout<<"red\n\n";
    }
    if(flag==yellow)
    {
        std::cout<<"yellow\n\n";
    }
    if(flag==green)
    {
        std::cout<<"green\n\n";
    }
}

double BotParameterPack::getDrawProbabilityHuman(unsigned int handValue)
{
    if(handValue<=14)
    {
        return 1;
    }
    if(handValue>18)
    {
        return 0;
    }
    switch(handValue)
    {
        case 15:
            return 0.95;
        case 16:
            return 0.80;
        case 17:
            return 0.5;
        case 18:
            return 0.05;
        default:
            throw ProbabilityMapValueNotPresent();
    }
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

double Bot::calculateAftermathWinningProbability(GameDeck knownDeck,HandDeck opponentDeck)
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

std::map<int, double> Bot::computeDistribution(HandDeck currentHand,
                                          GameDeck deck,
                                          int drawsSoFar = 0,
                                          double cumProb = 1.0)
{
    std::map<int, double> result;
    unsigned int value = currentHand.getGameValue();

    // Base Case 1: Bust
    if (value > 21) {
        result[0] = cumProb;
        return result;
    }

    // Base Case 2: Reached maximum of 5 cards
    if (drawsSoFar >= 5) {
        result[value] = cumProb;
        return result;
    }

    // IMPORTANT: If no cards remain, we must stop drawing
    if (deck.getNumberOfCards() == 0) {
        result[value] = cumProb;
        return result;
    }

    // Get probability that opponent decides to draw from this state.
    double pDraw = botParamPack.getDrawProbabilityHuman(value);

    std::map<int, double> dist;  // Will accumulate the distribution from both branches.

    // "Stop drawing" branch: even if pDraw < 1, the opponent might decide to stop.
    double pNoDraw = (1.0 - pDraw);
    if (pNoDraw > 0.0) {
        dist[value] += cumProb * pNoDraw;
    }

    // "Draw" branch: if the player decides to draw.
    if (pDraw > 0.0) {
        double totalCards = static_cast<double>(deck.getNumberOfCards());
        // For each card available in deck...
        for (unsigned int i = 0; i < deck.getNumberOfCards(); i++) {
            Card nextCard = deck.returnCardAtIndex(i);

            // Create a copy of the deck and remove the chosen card.
            GameDeck newDeck = deck;
            newDeck.removeCardAtIndex(i);

            // Create a copy of the current hand and add the new card.
            HandDeck newHand = currentHand;
            newHand.addCard(nextCard);

            // Update cumulative probability:
            // Multiply by pDraw (chance to draw at this state) and by the chance to pick this card.
            double newCumProb = cumProb * pDraw * (1.0 / totalCards);

            // Recurse with an extra card drawn.
            std::map<int, double> subDist = computeDistribution(newHand, newDeck, drawsSoFar + 1, newCumProb);
            for (auto &kv : subDist) {
                dist[kv.first] += kv.second;
            }
        }
    }

    return dist;
}

std::map<int, double> Bot::getOpponentProbabilities(HandDeck openHandDeck, GameDeck knownDeck)
{
    int drawsSoFar = openHandDeck.getNumberOfCards();
    std::map<int, double> distribution = computeDistribution(openHandDeck, knownDeck, drawsSoFar, 1.0);
    return distribution;
}

double Bot::getComplexWinProb(HandDeck opponentHand, GameDeck knownDeck)
{
    double assumedWinProb = getAssumedWinProbRaw(opponentHand,knownDeck);
    std::vector<HandDeck> combinationHands = getCombinationHands(knownDeck,opponentHand);
    double initialWinProbability = calculateInitialWinningProbability(combinationHands);

    return assumedWinProb*botParamPack.assumalWinProbWeight + initialWinProbability*(1-botParamPack.assumalWinProbWeight);

}

double Bot::getAssumedWinProbRaw(HandDeck opponentHand, GameDeck knownDeck)
{
    double assumedWinProb = 0;

    HandDeck openHandDeck = opponentHand.getOpenHand();

    unsigned int selfGameValue = getHandDeck().getGameValue();
    std::map<int, double> dist = getOpponentProbabilities(openHandDeck, knownDeck);
    for (auto &kv : dist)
    {
        if(kv.first<selfGameValue)
        {
            assumedWinProb+=kv.second;
        }
        else if(kv.first==selfGameValue)
        {
            assumedWinProb+=((kv.second)/2);
        }
    }

    return assumedWinProb;
}

Bot::Bot(std::string name, unsigned int deckMultiplier)
    : Player(name, deckMultiplier)
{

}

bool Bot::matchBetOrNot(unsigned int betRaiseForRound,HandDeck opponentDeck)
{

    double complexWinProb = getComplexWinProb(opponentDeck,getKnownDeck());
    std::cout<<complexWinProb<<"\n";

    if(complexWinProb<0.5)
    {
        return false;
    }
    float realMatchValue = std::ceil(complexWinProb*botParamPack.maxBetRaise);

    if(realMatchValue>=betRaiseForRound)
    {
        return true;
    }
    else
    {
        return false;
    }


}

double Bot::getExpectedValue(GameDeck knownDeck,HandDeck opponentDeck)
{

    double expectedValue = 0;
    double aftermathWinProbability = 0;

    std::vector<HandDeck> combinationHands = getCombinationHands(knownDeck,opponentDeck);
    double initialWinProbability = calculateInitialWinningProbability(combinationHands);


    for(HandDeck handDeck : combinationHands)
    {
        aftermathWinProbability = calculateAftermathWinningProbability(knownDeck,opponentDeck);
        expectedValue += (aftermathWinProbability-initialWinProbability);
    }

    return expectedValue;
}

unsigned int Bot::betRaiseOrNot(HandDeck opponentDeck, GameDeck knownDeck,unsigned int maxBetRaise)
{
    unsigned int betRaise;
    double complexWinProb = getComplexWinProb(opponentDeck,knownDeck);
    if(!getRandomBool(complexWinProb))
    {
        return 0;
    }

    if(complexWinProb<0.5)
    {
        //roll the dice again, this is no joke
        if(!getRandomBool(complexWinProb*botParamPack.bluffMultiplier))
        {
            return 0;
        }
    //ooh, spicy. we are bluffing!
        double randomDouble = getRandomDouble();
        betRaise = static_cast<unsigned int>(std::ceil(randomDouble) * maxBetRaise);
    }
    else
    {
        betRaise = static_cast<unsigned int>(std::ceil(complexWinProb) * maxBetRaise);
    }

    if(betRaise>getMoney())
    {
        betRaise = getMoney();
    }
    return betRaise;
}
double Bot::getRandomDouble() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.5, 1.0);

    return dis(gen);
}

bool Bot::getRandomBool(double probability)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    return dis(gen) < probability;

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
    std::vector<std::vector<unsigned int>> indexVector = generateCombinations(knownDeck.getNumberOfCards()
    ,numberOfUnknownCards);
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

