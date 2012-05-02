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
	undoinfo = new undoInfo;
	undoinfo->undone = 1;
	playerTime = 0;
}

Board::~Board()
{
	delete undoinfo;
}

void Board::incrementPlayerTime()
{
	playerTime++;
}

int Board::getPlayerTime()
{
	return playerTime;
}

void Board::deal()
{
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

void Board::setDrawNumber(int number)
{
	drawNumber = number;
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

int Board::pickCards(int colnum, int depth)
{

	if(column[colnum].getSize() > 0)
	{
		if(column[colnum].getFlip(depth) == 1)
		{
			movingFrom = colnum;
			column[PLAYER_HAND].pushSection(column[colnum].popSection(column[colnum].getSize()-depth));

		} else {
			if(column[colnum].getSize() > depth)
				if(column[colnum].getFlip(depth+1) == 1)
				{
					column[colnum].flipOver();
					undoinfo->undone = 1; //prevent against bad undos
				}
		}
	}

	return 1;
}

int Board::dropCards(int colnum)
{

	if(colnum == -1)
	{
		column[movingFrom].pushSection(column[PLAYER_HAND].popSection(column[PLAYER_HAND].getSize()));
		return 0;
	}

	if(colnum > 10)
	{
		if(putUp(PLAYER_HAND))
			return 1;
	}
	else if(column[colnum].getSize() > 0)
	{
		if(isAllowed(column[PLAYER_HAND].getVal(0), column[colnum].getVal(column[colnum].getSize() - 1)))
		{
			makeMove(movingFrom, colnum);
			return 1;
		}

	} else if(((column[PLAYER_HAND].getVal(0)+1) % 13 == 0) && (column[PLAYER_HAND].getVal(0) != 0))
	{
		makeMove(movingFrom, colnum);
		return 1;
	}

	column[movingFrom].pushSection(column[PLAYER_HAND].popSection(column[PLAYER_HAND].getSize()));
	return 0;
}

void Board::makeMove(int src, int dest)
{
	undoinfo->undone = 0;
	undoinfo->movingTo = dest;
	undoinfo->movingFrom = src;
	undoinfo->numCards = column[PLAYER_HAND].getSize();
	column[dest].pushSection(column[PLAYER_HAND].popSection(column[PLAYER_HAND].getSize()));
}

void Board::undo()
{
	if(!undoinfo->undone)
	{
		undoinfo->undone = 1;
		column[undoinfo->movingFrom].pushSection(column[undoinfo->movingTo].popSection(undoinfo->numCards));
	}
}

CardColumn Board::getColumn(int colNum)
{ //returns cardcolumn # colNum
	return(column[colNum]);
}

int Board::getDeckRemaining()
{
	return deck.getSize();
}

void Board::draw()
{
	int card;
	deque<int> deckpile;

	undoinfo->undone = 1; //prevent against bad undos

	if(deck.getSize() != 0)
	{
		column[OLD_DECK_DISCARD].pushSection(column[DECK_DISCARD].popSection(column[DECK_DISCARD].getSize()));
		for(int i = 0; i < drawNumber; i++)
		{
			card = deck.getCard();
			if(card != -1)
				column[DECK_DISCARD].setCard(card, 1);
		}
	} else {
		deckpile = column[OLD_DECK_DISCARD].popSection(column[OLD_DECK_DISCARD].getSize());

		for(unsigned int i = deckpile.size() - 1; i <= deckpile.size(); i--)
			deck.pushCard(deckpile[i]);

		deckpile = column[DECK_DISCARD].popSection(column[DECK_DISCARD].getSize());

		for(unsigned int i = deckpile.size() - 1; i <= deckpile.size(); i--)
			deck.pushCard(deckpile[i]);

		draw();
	}

}

int Board::putUp(int col_num)  //this funtion checks if a card can be moved to a foundation, and moves it if possible.
{
	int suit;

	if(column[col_num].getSize() == 0)
		return 0;

	int cardnum = column[col_num].getVal(column[col_num].getSize()-1);

	if (cardnum/13>=0) suit = 1; //diamonds
	if (cardnum/13>=1) suit = 2; //clubs
	if (cardnum/13>=2) suit = 3; //hearts
	if (cardnum/13>=3) suit = 4; //spades

	if(column[SUITPILE_OFFSET+suit].getSize() == 0)
	{
		if(cardnum % 13 == 0)
		{
			undoinfo->undone = 0;
			undoinfo->movingTo = SUITPILE_OFFSET+suit;
			undoinfo->movingFrom = col_num;
			undoinfo->numCards = 1;
			column[SUITPILE_OFFSET+suit].pushSection(column[col_num].popSection(1));
			return 1;
		}
	} else {
		if (cardnum%13 == (column[SUITPILE_OFFSET+suit].getVal(column[SUITPILE_OFFSET+suit].getSize()-1) % 13)+1)
		{
			undoinfo->undone = 0;
			undoinfo->movingTo = SUITPILE_OFFSET+suit;
			undoinfo->movingFrom = col_num;
			undoinfo->numCards = 1;
			column[SUITPILE_OFFSET+suit].pushSection(column[col_num].popSection(1));
			return 1;
		}
	}

	return 0;
}

