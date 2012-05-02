////////////////////////////////////////////////////////////////////////////////
// Board.h                                                                    //
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

#ifndef BOARD_H
#define BOARD_H
#include"CardDeck.h"
#include"CardColumn.h"

using namespace std;

typedef struct
{
	int movingFrom;
	int movingTo;
	int numCards;
	int undone;
} undoInfo;

enum
{
	PLAYER_HAND = 0,
	DECK_DISCARD = 9,
	OLD_DECK_DISCARD = 10,
	SUITPILE_OFFSET = 10
};

class Board
{

public:
	Board();
	~Board();
	void deal();                //deals out cards
	void setDrawNumber(int);
	void draw();                //draws cards from the deck
	void undo();                //undo last action, maximum 1 time
	void incrementPlayerTime(); //increments elapsed time by 1, used by qt easy timers
	int getPlayerTime();        //returns elapsed time in game
	int getDeckRemaining();     //returns number of cards in the deck
	CardColumn getColumn(int);	//returns cardcolumn 
	int putUp(int);             //(column) - puts up (column)'s top card in to the foundations, if possible.  returns 1 on success
	int pickCards(int, int);    //(column, depth) - picks up cards to user hand from (column, depth)
	int dropCards(int);         //(column, depth) - drops card from user hand appropriate to (column, unused)

private: 
	int isAllowed(int, int); 	//returns 1 if move from (src, dest) is possible
	int cardNumber(const int); 	//returns number of card (0 = Ace, 12=K)
	int suitNum(const int);		//returns 1 for red, 0 for black
	void makeMove(int, int);    //makes a move in to (unused, dest).  This inserts relvant information in to the undo structure.

	int drawNumber;             //number of cards to draw from the deck per turn
	int movingFrom;             //holds the column number we're moving from
	int playerTime;             //elapsed game time
	//Cardcolumns
	//0: Player hand
	//1-7 Each of the card stacks
	//8 not used
	//9 Deck discarded.
	//10 "Old" deck discarded.
	//11-14 Foundation piles.
	CardColumn column[15];
	CardDeck deck;
	undoInfo * undoinfo;
};
#endif

