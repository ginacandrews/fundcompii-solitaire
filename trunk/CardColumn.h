#ifndef CARDCOLUMN_H
#define CARDCOLUMN_H
#include"CardDeck.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
#include<deque>
#include<cstdlib>
#include<ctime>
using namespace std;

class CardColumn{

public:
CardColumn();
void setCard(int, int);
void print();
string cardValue(const int);
string cardSuit(const int);
void flipOver();
//deque<int> getColVals();
int getVal(int);

int getSize();
private:
deque<int> value;
deque<int> flip;

};

#endif

