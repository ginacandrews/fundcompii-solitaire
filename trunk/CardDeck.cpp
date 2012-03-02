////////////////////////////////////////////////////////////////////////////////
// CardDeck.cpp                                                               //
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
#include <deque>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include"CardDeck.h"

using namespace std;

CardDeck::CardDeck(){ //default constructor
int n=52;
	for(int i=0; i<n; i++){ 
	Deck.push_back(i);
	}
srand(time(0));
}

CardDeck::CardDeck(const int n){ //non-default constructor
	for(int i=0; i<n; i++){
	Deck.push_back(i);
	}
srand(time(0));
}



int CardDeck::getSize(){ //returns current deck size
return(Deck.size());
}

void CardDeck::shuffle(){ //shuffles cards
random_shuffle(Deck.begin(),Deck.end());
}

void CardDeck::startDeal(){


}

/*char CardDeck::cardValue(const int &card){ //returns card value as char 
char character;
int num = card%13+2;	
	switch (num){
	case 2:
	character = '2';
	break;
	case 3:
	character = '3';
	break;
	case 4:
	character = '4';
	break;
	case 5:
	character = '5';
	break;
	case 6:
	character = '6';
	break;
	case 7:
	character = '7';
	break;
	case 8:
	character = '8';
	break;
	case 9:
	character = '9';
	break;
	case 10:
	character = 'T';
	break;
	case 11:
	character = 'A';
	break;
	case 12:
	character = 'J';
	break;
	case 13:
	character = 'Q';
	break;
	case 14:
	character = 'K';
	break;
	}
return(character);
}*/

void CardDeck::newDeck(){
Deck.clear();
int n=52;
	for(int i=0; i<n; i++){ 
	Deck.push_back(i);
	}
}

int CardDeck::getCard(){
int card = Deck.front();
Deck.pop_front();
return(card);
}

