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

CardDeck::CardDeck(const int n)
{ //non-default constructor
	for(int i=0; i<n; i++){
		Deck.push_back(i);
	}
	srand(time(0));
}

int CardDeck::getSize()
{ //returns current deck size
	return(Deck.size());
}

void CardDeck::shuffle()
{ //shuffles cards
	random_shuffle(Deck.begin(),Deck.end());
}

void CardDeck::newDeck()
{
	int oldDeckSize = Deck.size();
	Deck.clear();
	for(int i=0; i<oldDeckSize; i++){ 
		Deck.push_back(i);
	}
}

int CardDeck::getCard()
{
	if(Deck.size() > 0)
	{
		int card = Deck.front();
		Deck.pop_front();
		return(card);
	} else return -1;
}

void CardDeck::pushCard(const int card)
{
	Deck.push_back(card);
}