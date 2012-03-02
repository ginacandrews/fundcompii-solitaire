#ifndef CARDDECK_H
#define CARDDECK_H
#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
#include<deque>
#include<cstdlib>
#include<ctime>
using namespace std;

class CardDeck {

public:
CardDeck(); //constructors
CardDeck(const int);
int getSize(); //returns deck dize
void shuffle(); //shuffles deck
void startDeal(); //deals starting cards
//char cardValue(const int &); //returns char value of card 
void newDeck();
int getCard();
private:
deque<int> Deck; //deck of 52 cards
};

#endif
