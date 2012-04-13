////////////////////////////////////////////////////////////////////////////////
// SolGUI.cpp                                                               //
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

#include <QtGui>
#include <stdio.h>
#include <iostream>

#include "SolGUI.h"
#include "CardDeck.h"
#include "CardColumn.h"
#include "Board.h"

using namespace std;

SolGUI::SolGUI()
{
	cardImage = new QImage[52];
	cardBack = new QImage;

	this->setStyleSheet("background-color: darkgreen;");

	setWindowTitle(tr("Solitaire GUI"));
	resize(1024, 768);

	//image loading code in resize function, since we just called it, and it will be called to rescale the images

	setUpSnapLocs();

	board.deal();
	board.draw();

	dragx = 0;
	dragy = 0;
	mouseDown = 0;
}

void SolGUI::paintEvent(QPaintEvent*)
{
	CardColumn cardColumn;
	QPainter qpainter(this);

	for(int i = 1; i < 9; i++)
	{
		cardColumn = board.getColumn(i);
		for(int j = 0; j < cardColumn.getSize(); j++)
		{
			if (i == 8) //deck
			{
				qpainter.drawImage(snapLocs[i].width()*ratio+j*35*ratio, snapLocs[i].height()*ratio, cardImage[cardColumn.getVal(j)]);
			} else { //all other columns
				if(cardColumn.getFlip(j) == 1)
					qpainter.drawImage(snapLocs[i].width()*ratio, snapLocs[i].height()*ratio+j*25*ratio, cardImage[cardColumn.getVal(j)]);
				else
					qpainter.drawImage(snapLocs[i].width()*ratio, snapLocs[i].height()*ratio+(float(j*25)*ratio), *cardBack);
			}
		}
	}

	if (board.getDeckRemaining() > 0)
		qpainter.drawImage(20*ratio, 20*ratio, *cardBack);
}

QSize SolGUI::snapCardPos(QSize loc)
{


}

void SolGUI::setUpSnapLocs()
{
	snapLocs = new QSize[9];

	for(int i = 1; i < 8; i++)
		snapLocs[i] = QSize(20+170*(i-1), 350);

	snapLocs[8] = QSize(190, 20); //deck

}

void SolGUI::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton) {
		mouseDown = 1;


		board.draw();
	}

	e->accept();
	update();
}

void SolGUI::resizeEvent(QResizeEvent *e)
{
	QString filename;
	string file;

	if (e->oldSize().height() == -1)
		return;

	ratio = .7f*float(e->size().height() / float(768));

	QSize size(150*ratio, 217*ratio);

	for(int i = 0; i < 52; i++)
	{
		//file = "resources/" + cardSuit(i) + "-" + cardValue(i) + "-150.png";
		file = "resources/clubs-2-150.png";
		filename = QString::fromStdString(file);
		cardImage[i].load(filename);
		cardImage[i] = cardImage[i].scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	}

	cardBack->load("resources/back-red-150-1.png");
	*cardBack = cardBack->scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

	screenWidth = e->size().width();
	screenHeight = e->size().height();
}

void SolGUI::mouseMoveEvent(QMouseEvent *e)
{
	setCursor(Qt::ClosedHandCursor);
	dragx = e->x();
	dragy = e->y();
	update();
}

void SolGUI::mouseReleaseEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton) {
		setCursor(Qt::OpenHandCursor);
		dragx = e->x();
		dragy = e->y();
		mouseDown = 0;
		update();
	}
}

string SolGUI::cardValue(const int cardnum){ //returns card value as char 
	string character;
	char buff[10];
	int num = cardnum%13;	
	switch (num)
	{
	case 0:
		character = "a";
		break;
	case 10:
		character = "j";
		break;
	case 11:
		character = "q";
		break;
	case 12:
		character = "k";
		break;
	default:
		sprintf(buff, "%d", num+1);
		character = buff;
		break;
	}
	return(character);
}

string SolGUI::cardSuit(const int cardnum){
	string suit;
	if (cardnum/13>=0) suit = "diamonds";
	if (cardnum/13>=1) suit = "clubs";
	if (cardnum/13>=2) suit = "hearts";
	if (cardnum/13>=3) suit = "spades";
	return (suit);
}