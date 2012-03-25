////////////////////////////////////////////////////////////////////////////////
// Board.cpp                                                                  //
//  (c) Gina Andrews, Eric Vaughn, Aubrey Zielinski                           //
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//    This file is part of Fundamentals of Computing II Solitaire Group.      //
//                                                                            //
//    This program is free software: you can redistribute it and/or modify    //
//    it under the terms of the GNU General Public License as published by    //
//    the Free Software Foundation, either version 3 of the License, or       //
//    (at your option) any later version.                                     //
//                                                                            //
//    This program is distributed in the hope that it will be useful,         //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of          //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           //
//    GNU General Public License for more details.                            //
//                                                                            //
//    You should have received a copy of the GNU General Public License       //
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.   //
////////////////////////////////////////////////////////////////////////////////

#include<iostream>
#include<deque>

#include"CardDeck.h"
#include"CardColumn.h"
#include"Board.h"

using namespace std;

Board::Board(){
}

void Board::deal(){
	int flp=0;
	deck.newDeck();
	deck.shuffle();
	for (int i = 7; i> 0; i--){
		for (int j = 0; j<i; j++){
			if (j==i-1) flp=1;
			else flp=0;
			column[i].setCard(deck.getCard(),flp);
		}
	}

	drawNumber = 3;
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
	if (topnum == bottomnum-1) { 
		if (topsuit!=bottomsuit) return(1);
	}
	return(0);
}

int Board::moveCards(int srccolnum, int srccolcard, int destcolnum){ //copies sourcecolumn starting at srccolcard deep to destcol

	if (isAllowed(column[srccolnum].getVal(column[srccolnum].getSize() - srccolcard), column[destcolnum].getVal(column[destcolnum].getSize() - 1)))
	{
		column[destcolnum].pushSection(column[srccolnum].popSection(srccolcard));
		return 1;
	} else return 0;

}

CardColumn Board::getColumn(int colNum){ //returns cardcolumn # colNum
	return(column[colNum]);
}

void Board::setColumn(CardColumn bottom,int colNum){ //sets cardcolumn # colNum to bottom
	column[colNum]=bottom;
}

int Board::getDeckRemaining()
{
	return deck.getSize();
}

void Board::draw()
{
	for(int i = 0; i < drawNumber; i++)
		column[8].setCard(deck.getCard(), 1);
}

