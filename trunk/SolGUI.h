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
	void redeal();
	void undo();
	void incrementPlayerTime();
	int getPlayerScore();
	int getPlayedTime();
	void changeCardBack(int);
protected:
	void paintEvent(QPaintEvent*);
	void mousePressEvent(QMouseEvent*);
	void mouseMoveEvent(QMouseEvent*);
	void mouseReleaseEvent(QMouseEvent*);
	void resizeEvent(QResizeEvent*);
	void mouseDoubleClickEvent(QMouseEvent*);
private:
	void setUpSnapLocs();
	void reloadAssets();
	void rescaleAssets();
	void getCardSelectLoc(int, int);
	void returnCards();

	Board * board;

	QSize *snapLocs;
	QSize *suitsnapLocs;
	QSize deckLoc;
	QSize *topLocs;

	QImage *origcardImage;
	QImage *origcardBack;
	QImage *origsuitBack;
	QImage *origdeckBlank;

	QImage *cardImage;
	QImage *cardBack;
	QImage *suitBack;
	QImage *deckBlank;

	string cardValue(const int);
	string cardSuit(const int);

	int cardBackNumber;

	int screenWidth;
	int screenHeight;
	float ratio;

	//Drag variables
	int mouseDown;
	int dragx;
	int dragy;
};

#endif