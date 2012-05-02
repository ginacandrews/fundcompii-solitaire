////////////////////////////////////////////////////////////////////////////////
// SolGUI.h                                                               //
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

#ifndef SOLGUI_H
#define SOLGUI_H

#include <string>
#include <iostream>
#include <QWidget>
#include <QtGui>

#include "Board.h"

using namespace std;

class SolGUI : public QWidget
{
	 Q_OBJECT

public:
	SolGUI();
	~SolGUI();
	//The following public functions delegate control to board, and are menu functions from QtMain
	void redeal();             //resets board
	void setDrawNumber1();     //sets draw number to 1
	void setDrawNumber3();     //sets draw number to 3
	void undo();               //undos last move
	void incrementPlayerTime();//increments game time by 1 sec
	int getPlayerScore();      //returns player score
	int getPlayedTime();       //returns played time
	int getGameOver();         //gets the game over state
	void changeCardBack(int);  //changes card back to number
protected:
	//Qt inherited functions
	void paintEvent(QPaintEvent*);
	void mousePressEvent(QMouseEvent*);
	void mouseMoveEvent(QMouseEvent*);
	void mouseReleaseEvent(QMouseEvent*);
	void resizeEvent(QResizeEvent*);
	void mouseDoubleClickEvent(QMouseEvent*);
private:
	void setUpSnapLocs();      //sets up the locations for all of the cards
	void reloadAssets();       //reloads the files for all the card images
	void rescaleAssets();      //rescales the images in memory to the appropriate window size
	void getCardSelectLoc(int, int);   //calls the correct function in board for manipulating cards

	Board * board;             //pointer to our current board

	QSize *snapLocs;           //locations for card stacks
	QSize *suitsnapLocs;       //locations for suit piles
	QSize deckLoc;             //location for the deck

	//QImage pointers to array that contain the original full-resolution card art
	QImage *origcardImage;
	QImage *origcardBack;
	QImage *origsuitBack;
	QImage *origdeckBlank;

	//QImage pointers to array that contain the scaled card art
	QImage *cardImage;
	QImage *cardBack;
	QImage *suitBack;
	QImage *deckBlank;

	//returns card absolute number to card values and suits for loading from file
	string cardValue(const int);
	string cardSuit(const int);

	int drawNumber; //number of cards to draw out of the deck
	int cardBackNumber; //current selected card back

	//general screen values
	int screenWidth;
	int screenHeight;
	float ratio;

	//Drag variables
	int mouseDown;
	int dragx;
	int dragy;
};

#endif