////////////////////////////////////////////////////////////////////////////////
// CardColumn.h                                                               //
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
#ifndef CARDCOLUMN_H
#define CARDCOLUMN_H

#include<deque>

using namespace std;

class CardColumn{

public:
	CardColumn();
	void setCard(int, int);
	void print();
	void flipOver();
	int getVal(int);
	int getFlip(int);
	deque<int> popSection(int);  //functions for pushing and popping sections of the column
	void pushSection(deque<int>);//
	int getSize();

private:
	deque<int> value;
	deque<int> flip;

};

#endif

