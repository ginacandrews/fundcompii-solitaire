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
#include <stdio.h>
#include <string>
#include <deque>

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
	char * buff;
	int num = cardnum%13;	
	switch (num){
	case 0:
		character = "Ace";
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
	default:
		sprintf(buff, "%d", num++);
		character = buff;
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

int CardColumn::getVal(int position){ //returns value at position
	return(value[position]);
}

deque<int> CardColumn::popSection(int numDeep){
	deque<int> tempSection;
	for (int i = 0; i < numDeep; i++)
	{
		tempSection.push_back(value.back());
		value.pop_back();
	}
	return tempSection;
}

void CardColumn::pushSection(deque<int> section){

	for(int i = 0; i < section.size(); i++)
	{
		value.push_back(section.front());
		section.pop_front();
	}

}

int CardColumn::getSize(){ //returns size of that column
	return(value.size());
}
