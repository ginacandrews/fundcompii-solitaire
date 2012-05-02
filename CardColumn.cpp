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

#include"CardColumn.h"

using namespace std;

CardColumn::CardColumn(){
}

void CardColumn::setCard(int card, int flp){
	//cout<<card<<" "<<flp<<endl;
	value.push_back(card);
	flip.push_back(flp);

}


void CardColumn::print(){  //prints out card numberes, for testing purposes only
	for (unsigned int i=0; i<value.size(); i++){
		cout<<"("<<value[i]<<","<<flip[i]<<")";
		//if (flip[i]==0) cout<<"X  ";
		//else cout<<cardValue(value[i])<<" of "<<cardSuit(value[i]);
	}
}

void CardColumn::flipOver(){ //flips over card if the last card is unflipped, unused 
	if(flip.back()==0) {
		flip.pop_back();
		flip.push_back(1);
	}
}

int CardColumn::getVal(int position){ //returns value at position
	return(value[position]);
}

int CardColumn::getFlip(int position)  //gets flip value of position
{
	return(flip[position]);
}

deque<int> CardColumn::popSection(int numDeep){  //pops out a selection of cards, from the last card to numdeep, used for moving cards
	deque<int> tempSection;
	for (int i = 0; i < numDeep; i++)
	{
		tempSection.push_back(value.back());
		value.pop_back();
		flip.pop_back();
	}
	return tempSection;
}

void CardColumn::pushSection(deque<int> section){  //pushes multiple cards into a deque, used for moving cards

	while(section.size() > 0)
	{
		value.push_back(section.back());
		flip.push_back(1);
		section.pop_back();
	}

}

int CardColumn::getSize(){ //returns size of that column
	return(value.size());
}

