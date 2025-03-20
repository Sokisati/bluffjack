//
// Created by hal_9000 on 2025-03-12.
//

#ifndef CARD_H
#define CARD_H

enum CardSuit {SPADES,HEARTS,DIAMONDS,CLUBS};
enum CardType {TWO=2,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,A,K,Q,J};
enum CardState {up,down};

class Card
{
    CardSuit cardSuit;
    CardType cardType;
    CardState cardState = down;

public:

    Card(CardSuit cardSuit,CardType cardType);
    unsigned int getCardValue();
    void flipCard();
    bool operator==(Card cardToCompare);
    CardSuit getCardSuit();
    CardType getCardType();
    CardState getCardState();
    void printCard();
    void openCard();
    void closeCard();
};



#endif //CARD_H
