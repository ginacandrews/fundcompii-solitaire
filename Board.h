#ifndef BOARD_H
#define BOARD_H
#include"CardDeck.h"
#include"CardColumn.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
#include<deque>
#include<cstdlib>
#include<ctime>
using namespace std;

class Board{

public:
Board();
void deal();			//deals out cards
void print();			//prints out all the columns
int isAllowed(int, int); 	//returns 1 if it's allowed 
int cardNumber(const int); 	//returns number of card (0 = Ace, 12=K)
int suitNum(const int);		//returns 1 for red, 0 for black
CardColumn moveCards(CardColumn, CardColumn); 	//copies first parameter cardcolumn to the end of the second cardcolumn
CardColumn getColumn(int);	//returns cardcolumn 
void setColumn(CardColumn,int);	//sets cardcolumn # int
private: 
CardColumn column[20];
CardDeck deck;
};
#endif

