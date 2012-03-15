////////////////////////////////////////////////////////////////////////////////
// main.cpp                                                                   //
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

#include <iostream>

#include "CardDeck.h"
#include "CardColumn.h"
#include "Board.h"

using namespace std;

int main ( int argc, char *argv[] )
{
	Board board; 
	board.deal();
	board.print();

	int allowed = board.isAllowed(0,14);
	cout<<"is allowed is: "<<allowed<<endl<<"copying column 2 to column 3"<<endl<<endl;
	/*
	CardColumn temp;
	int top=2; int bottom=3;
	temp = board.moveCards(board.getColumn(top),board.getColumn(bottom)); 
	board.setColumn(temp,bottom);

	board.print();*/
	return (0);
}
