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

Board::Board()
{

}

Board::~Board()
{

}

void Board::deal(){
	int flp=0;
	deck.newDeck();
	deck.shuffle();
	for (int i = 7; i> 0; i--){  //these two loops set the starting columns.
		for (int j = 0; j<i; j++){
			if (j==i-1) flp=1; //flips over last card
			else flp=0;
			column[i].setCard(deck.getCard(),flp); //sets column card here
		}
	}

	drawNumber = 3; //how many cards the draw stack flips at a time
}

void Board::print(){  //this code was used to test in the terminal, no longer used
	for(int i=7; i>0; i--){
		cout<<"column "<<i<<":";
		column[i].print();
		cout<<endl;
	}
}

int Board::cardNumber(const int cardnum){ //returns card value as num (0-12)
	int num = cardnum%13;	
	return(num);
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

int Board::moveCards(int srccolnum, int srccolcard, int destcolnum, int safe){ //copies sourcecolumn starting at srccolcard deep to destcol


	if(srccolnum == 8) //moving to and from the deck
	{
		column[destcolnum].pushSection(deckdiscard.popSection(srccolcard));
	} else if (destcolnum == 8)
	{
		deckdiscard.pushSection(column[srccolnum].popSection(srccolcard));
	} else if(safe)
	{
		if(column[destcolnum].getSize() == 0)
		{//allow for kings dropping on to empty columns
			if(cardNumber(column[srccolnum].getVal(column[srccolnum].getSize() - srccolcard)) % 12 == 0)
			{
				column[destcolnum].pushSection(column[srccolnum].popSection(srccolcard));
				return 1;
			}
		} else if (isAllowed(column[srccolnum].getVal(column[srccolnum].getSize() - srccolcard), column[destcolnum].getVal(column[destcolnum].getSize() - 1)))
		{//normal card movement check
			column[destcolnum].pushSection(column[srccolnum].popSection(srccolcard));
			return 1;
		} else return 0;
	} else {//else if we're making a forced move
		column[destcolnum].pushSection(column[srccolnum].popSection(srccolcard));
		return 1;
	}

}

CardColumn Board::getColumn(int colNum)
{ //returns cardcolumn # colNum
	return(column[colNum]);
}

CardColumn Board::getDeckDiscard()
{
	return deckdiscard;
}

CardColumn Board::getSuitPile(int pileNum)
{
	return(suitpiles[pileNum]);
}

void Board::setColumn(CardColumn bottom,int colNum){ //sets cardcolumn # colNum to bottom
	column[colNum]=bottom;
}

int Board::getDeckRemaining()
{
	return deck.getSize();
}

int Board::flipColumn(int col)
{
	column[col].flipOver();

	return 1;
}

void Board::draw()
{
	int card;
	deque<int> deckpile;

	if(deck.getSize() != 0)
	{
		olddeckdiscard.pushSection(deckdiscard.popSection(deckdiscard.getSize()));
		for(int i = 0; i < drawNumber; i++)
		{
			card = deck.getCard();
			if(card != -1)
				deckdiscard.setCard(card, 1);
		}
	} else {
		deckpile = olddeckdiscard.popSection(olddeckdiscard.getSize());

		for(unsigned int i = deckpile.size() - 1; i <= deckpile.size(); i--)
			deck.pushCard(deckpile[i]);

		deckpile = deckdiscard.popSection(deckdiscard.getSize());

		for(unsigned int i = deckpile.size() - 1; i <= deckpile.size(); i--)
			deck.pushCard(deckpile[i]);

		draw();
	}

}

int Board::putUp(int cardnum, int col_num)  //this funtion checks if a card can be moved to a foundation, and moves it if possible.
{
	int suit;

	if (cardnum/13>=0) suit = 1; //diamonds
	if (cardnum/13>=1) suit = 2; //clubs
	if (cardnum/13>=2) suit = 3; //hearts
	if (cardnum/13>=3) suit = 4; //spades
	

	if(suitpiles[suit].getSize() == 0)
	{
		if(cardnum % 13 == 0)
		{
			suitpiles[suit].pushSection(column[col_num].popSection(1));
			return 1;
		}
	} else {
		if (cardnum%13 == (suitpiles[suit].getVal(suitpiles[suit].getSize()-1) % 13)+1)
		{
			suitpiles[suit].pushSection(column[col_num].popSection(1));
			return 1;
		}
	}

	return 0;
}

