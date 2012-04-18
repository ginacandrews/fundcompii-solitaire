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
protected:
	void paintEvent(QPaintEvent*);
	void mousePressEvent(QMouseEvent*);
	void mouseMoveEvent(QMouseEvent*);
	void mouseReleaseEvent(QMouseEvent*);
	void resizeEvent(QResizeEvent*);
private:
	void setUpSnapLocs();
	QSize snapCardPos(QSize loc);
	void getCardSelectLoc(int, int);

	Board board;
	QSize *snapLocs;
	QSize deckLoc;
	QSize *topLocs;
	string cardValue(const int);
	string cardSuit(const int);
	QImage *cardImage;
	QImage *cardBack;
	int screenWidth;
	int screenHeight;
	float ratio;

	//Drag variables
	int mouseDown;
	int movingFrom;
	int dragx;
	int dragy;
};