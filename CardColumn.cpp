#include"CardDeck.h"
#include"CardColumn.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
#include<deque>
#include<cstdlib>
#include<ctime>
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
