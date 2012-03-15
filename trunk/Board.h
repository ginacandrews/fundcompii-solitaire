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

