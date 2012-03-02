////////////////////////////////////////////////////////////////////////////////
// CardColumn.cpp                                                             //
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
#include <string>
#include <deque>

#include"CardDeck.h"
#include"CardColumn.h"

using namespace std;

CardColumn::CardColumn(){
}

void CardColumn::setCard(int card, int flp){
//cout<<card<<" "<<flp<<endl;
value.push_back(card);
flip.push_back(flp);

}


void CardColumn::print(){
	for (int i=0; i<value.size(); i++){
	cout<<"("<<value[i]<<","<<flip[i]<<")";
		//if (flip[i]==0) cout<<"X  ";
		//else cout<<cardValue(value[i])<<" of "<<cardSuit(value[i]);
	}
}

string CardColumn::cardValue(const int cardnum){ //returns card value as char 
string character;
int num = cardnum%13;	
	switch (num){
	case 0:
	character = "Ace";
	break;
	case 1:
	character = "2";
	break;
	case 2:
	character = "3";
	break;
	case 3:
	character = "4";
	break;
	case 4:
	character = "5";
	break;
	case 5:
	character = "6";
	break;
	case 6:
	character = "7";
	break;
	case 7:
	character = "8";
	break;
	case 8:
	character = "9";
	break;
	case 9:
	character = "10";
	break;
	case 10:
	character = "Jack";
	break;
	case 11:
	character = "Queen";
	break;
	case 12:
	character = "King";
	break;
	}
return(character);
}

string CardColumn::cardSuit(const int cardnum){
string suit;
	if (cardnum/13>=0) suit = "Diamonds";
	if (cardnum/13>=1) suit = "Clubs";
	if (cardnum/13>=2) suit = "Hearts";
	if (cardnum/13>=3) suit = "Spades";
return (suit);
}

void CardColumn::flipOver(){
	if(flip.back()==0) {
	flip.pop_back();
	flip.push_back(1);
	}
}
/*
deque<int> CardColumn::getColVals(){ //returns deque of values
return(value);
}
*/
int CardColumn::getVal(int position){ //returns value at position
return(value[position]);
}

int CardColumn::getSize(){ //returns size of that column
return(value.size());
}
