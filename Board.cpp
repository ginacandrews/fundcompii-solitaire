#include"CardDeck.h"
#include"CardColumn.h"
#include"Board.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
#include<deque>
#include<cstdlib>
#include<ctime>
using namespace std;

Board::Board(){
}

void Board::deal(){
int flp=0;
deck.shuffle();
for (int i = 7; i> 0; i--){
	for (int j = 0; j<i; j++){
		if (j==i-1) flp=1;
		else flp=0;
		column[i].setCard(deck.getCard(),flp);
	}
}
}

void Board::print(){
	for(int i=7; i>0; i--){
		cout<<"column "<<i<<":";
		column[i].print();
		cout<<endl;
	}
}

int Board::cardNumber(const int cardnum){ //returns card value as num 
int card;
int num = cardnum%13;	
	switch (num){
	case 0:
	card=1;
	break;
	case 1:
	card=2;
	break;
	case 2:
	card=3;
	break;
	case 3:
	card=4;
	break;
	case 4:
	card=5;
	break;
	case 5:
	card=6;
	break;
	case 6:
	card=7;
	break;
	case 7:
	card=8;
	break;
	case 8:
	card=9;
	break;
	case 9:
	card=10;
	break;
	case 10:
	card=11;
	break;
	case 11:
	card=12;
	break;
	case 12:
	card=13;
	break;
	}
return(card);
}

int Board::suitNum(const int cardnum){ //returns suit number
int suit; //0 = black, 1 = red
	if (cardnum/13>=0) suit = 1; //if diamonds, suit = 1 for red
	if (cardnum/13>=1) suit = 0; //if clubs, suit = 0
	if (cardnum/13>=2) suit = 1; //if hearts, suit = 1
	if (cardnum/13>=3) suit = 0; //if spates, suit =0
return (suit);
}

int Board::isAllowed(int top, int bottom){ //returns 1 if move from top to bottom is allowed
int topnum=cardNumber(top);
int bottomnum=cardNumber(bottom);
int topsuit=suitNum(top);
int bottomsuit=suitNum(bottom);
	if (topnum=bottomnum-1) { 
		if (topsuit!=bottomsuit) return(1);
	}
return(0);
}

CardColumn Board::moveCards(CardColumn topcol, CardColumn bottomcol){ //copies topcol to bottomcol
	for (int i=0; i<topcol.getSize(); i++){
	bottomcol.setCard(topcol.getVal(i),1);
	}
return(bottomcol);
}

CardColumn Board::getColumn(int colNum){ //returns cardcolumn # colNum
return(column[colNum]);
}

void Board::setColumn(CardColumn bottom,int colNum){ //sets cardcolumn # colNum to bottom
column[colNum]=bottom;
}

















