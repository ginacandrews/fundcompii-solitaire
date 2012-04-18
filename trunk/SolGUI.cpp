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

	update();

	dragx = 0;
	dragy = 0;
	mouseDown = 0;
}

void SolGUI::paintEvent(QPaintEvent*)
{
	CardColumn cardColumn;
	QPainter qpainter(this);

	for(int i = 1; i < 8; i++)
	{
		cardColumn = board.getColumn(i);
		for(int j = 0; j < cardColumn.getSize(); j++)
		{
				if(cardColumn.getFlip(j) == 1)
					qpainter.drawImage(snapLocs[i].width()*ratio-((cardImage[cardColumn.getVal(j)].width())/2), snapLocs[i].height()*ratio+j*35*ratio-((cardImage[cardColumn.getVal(j)].height())/2), cardImage[cardColumn.getVal(j)]);
				else
					qpainter.drawImage(snapLocs[i].width()*ratio-((cardImage[cardColumn.getVal(j)].width())/2), snapLocs[i].height()*ratio+(float(j*35)*ratio)-((cardImage[cardColumn.getVal(j)].height())/2), *cardBack);
		}
	}

	for(int i = 0; i < board.getDeckDiscard().getSize(); i++)
		qpainter.drawImage(deckLoc.width()*ratio+i*35*ratio, deckLoc.height()*ratio, cardImage[board.getDeckDiscard().getVal(i)]);

	for(int i = 1; i < 5; i++)
		//draw each suit pile top card

	if (board.getDeckRemaining() > 0)
		qpainter.drawImage(20*ratio, 20*ratio, *cardBack);

	if(mouseDown) //if mouse is held down, draw the stack we could be holding.
	{
		cardColumn = board.getColumn(0);
		for(int i = 0; i < cardColumn.getSize(); i++)
			qpainter.drawImage(dragx-((cardImage[cardColumn.getVal(i)].width())/2), dragy+i*35*ratio-((cardImage[cardColumn.getVal(i)].height())/2), cardImage[cardColumn.getVal(i)]);
	}
}

QSize SolGUI::snapCardPos(QSize loc)
{


}

void SolGUI::setUpSnapLocs()
{
	snapLocs = new QSize[9];

	for(int i = 1; i < 8; i++)
		snapLocs[i] = QSize(100+170*(i-1), 370);

	deckLoc = QSize(190, 20); //deck

}

void SolGUI::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton) {
		mouseDown = 1;
		dragx = e->x();
		dragy = e->y();
		getCardSelectLoc(e->x(), e->y()); //pushes cards in to the "holding vector"
		//board.draw();
	}

	e->accept();
	update();
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
		getCardSelectLoc(e->x(), e->y());
	}
	update();
}

void SolGUI::getCardSelectLoc(int x, int y)
{
	CardColumn cardColumn;
	CardColumn emptyColumn;

	for(int i = 1; i < 8; i++) //There are better ways to do this than an iterative approach, but it works just as well.
	{
		cardColumn = board.getColumn(i);
		for(int j = cardColumn.getSize()-1; j >= 0; j--)
			if(x < (snapLocs[i].width()*ratio+(cardBack->width()/2)) && x > (snapLocs[i].width()*ratio-(cardBack->width()/2))
				&& y < (snapLocs[i].height()*ratio+j*35*ratio+(cardBack->height()/2)) && y > (snapLocs[i].height()*ratio+j*35*ratio-(cardBack->height()/2)))
			{
				//At this point, i will be the column number (from the left) and j will be the depth in that column.

				if(mouseDown)
				{//we're selecting a fresh stack.
					cardColumn=board.getColumn(i);
					if(cardColumn.getFlip(j)) //if this is a valid selection
					{
						board.moveCards(i, cardColumn.getSize()-j, 0, 0);
						movingFrom=i;
					} //TODO: } else { if top card in stack, flip over
				}
				else
				{//we might be dropping a stack
					cardColumn=board.getColumn(0);
					//////////////BUG//////write in if(holding cards) check here
					if(!board.moveCards(0, cardColumn.getSize(), i, 1))  //try to ove cards to the stack we're over
						board.moveCards(0, cardColumn.getSize(), movingFrom, 0); //if that doesn't work, pop them back where they came from
				}
				return;
			}
	}

	//we only get to this point if we didn't find a valid stack to pull from or drop on.
	// This code "snaps" cards back to their original stack if we're holding cards and just let go of the mouse button
	cardColumn=board.getColumn(0);
	if (!mouseDown && cardColumn.getSize() > 0)
		board.moveCards(0, cardColumn.getSize(), movingFrom, 0);



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
		file = "resources/" + cardSuit(i) + "-" + cardValue(i) + "-150.png";
		cardImage[i].load(QString(file.c_str()));
		cardImage[i] = cardImage[i].scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	}

	cardBack->load("resources/back-red-150-1.png");
	*cardBack = cardBack->scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

	screenWidth = e->size().width();
	screenHeight = e->size().height();
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