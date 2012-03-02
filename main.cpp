#include"CardDeck.h"
#include"CardColumn.h"
#include"Board.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
#include<deque>
#include<cstdlib>
#include<ctime>
#include"CardDeck.h"
using namespace std;

int main (){
Board board; 
board.deal();
board.print();

int allowed = board.isAllowed(0,14);
cout<<"is allowed is: "<<allowed<<endl<<"copying column 2 to column 3"<<endl<<endl;

CardColumn temp;
int top=2; int bottom=3;
temp = board.moveCards(board.getColumn(top),board.getColumn(bottom)); 
board.setColumn(temp,bottom);

board.print();
return (0);
}
