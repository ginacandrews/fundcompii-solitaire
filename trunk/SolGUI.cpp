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
	suitBack = new QImage[5];
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

	//draw columns
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

	//draw deck discard
	for(int i = 0; i < board.getDeckDiscard().getSize(); i++)
		qpainter.drawImage(deckLoc.width()*ratio+170*ratio+i*35*ratio-((cardBack->width())/2), deckLoc.height()*ratio-((cardBack->height())/2), cardImage[board.getDeckDiscard().getVal(i)]);

	//draw each suit pile top card
	for(int i = 1; i < 5; i++)
	{
		qpainter.drawImage(suitsnapLocs[i].width()*ratio-((cardBack->width())/2), suitsnapLocs[i].height()*ratio-((cardBack->height())/2), suitBack[i]);
		if(board.getSuitPile(i).getSize() != 0)
			qpainter.drawImage(suitsnapLocs[i].width()*ratio-((cardBack->width())/2), suitsnapLocs[i].height()*ratio-((cardBack->height())/2), cardImage[board.getSuitPile(i).getVal(board.getSuitPile(i).getSize() - 1)]);
	}

	//draw deck location
	if (board.getDeckRemaining() > 0)
		qpainter.drawImage(deckLoc.width()*ratio-((cardBack->width())/2), deckLoc.height()*ratio-((cardBack->height())/2), *cardBack);

	//if mouse is held down, draw the stack we could be holding.
	if(mouseDown) 
	{
		cardColumn = board.getColumn(0);
		for(int i = 0; i < cardColumn.getSize(); i++)
			qpainter.drawImage(dragx-((cardImage[cardColumn.getVal(i)].width())/2), dragy+i*35*ratio-((cardImage[cardColumn.getVal(i)].height())/2), cardImage[cardColumn.getVal(i)]);
	}
}

void SolGUI::setUpSnapLocs()
{//sets up an array of static locations on the field where cards should go
	snapLocs = new QSize[9];
	suitsnapLocs = new QSize[5];

	for(int i = 1; i < 8; i++)
		snapLocs[i] = QSize(100+170*(i-1), 370);

	for(int i = 1; i < 5; i++)
		suitsnapLocs[i] = QSize(610+170*(i-1), 125);

	deckLoc = QSize(115, 125); //deck

}

void SolGUI::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton) {
		mouseDown = 1;
		dragx = e->x();
		dragy = e->y();
		getCardSelectLoc(e->x(), e->y()); //pushes cards in to the "holding vector"
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

void SolGUI::mouseDoubleClickEvent(QMouseEvent *e)
{
	CardColumn cardColumn;
	int x = e->x();
	int y = e->y();

	if (e->button() == Qt::LeftButton) {

		for(int i = 1; i < 8; i++) //There are better ways to do this than an iterative approach, but it works just as well.
		{
			cardColumn = board.getColumn(i);
			for(int j = (((cardColumn.getSize()-1) == -1) ? 0 : cardColumn.getSize()-1); j >= 0; j--)
				if(x < (snapLocs[i].width()*ratio+(cardBack->width()/2)) && x > (snapLocs[i].width()*ratio-(cardBack->width()/2))
					&& y < (snapLocs[i].height()*ratio+j*35*ratio+(cardBack->height()/2)) && y > (snapLocs[i].height()*ratio+j*35*ratio-(cardBack->height()/2)))
				{
					if(j == cardColumn.getSize()-1)
						board.putUp(board.getColumn(i).getVal(j), i);
				}
		}
	}
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
	int cardColSize;
	CardColumn emptyColumn;

	//if we click the deck
	if(x < deckLoc.width()*ratio+(cardBack->width()/2) && x > deckLoc.width()*ratio-(cardBack->width()/2)
		&& y > deckLoc.height()*ratio-(cardBack->height()/2) && y < deckLoc.height()*ratio+(cardBack->height()/2)
		&& mouseDown)
	{
		board.draw();
		return;
	}

	//if we click the deck discard pile
	int i = (((board.getDeckDiscard().getSize() % 3) == 0) ? 3 : board.getDeckDiscard().getSize() % 3);
	if(x < deckLoc.width()*ratio+170*ratio+i*35*ratio+((cardBack->width())/2) && x > deckLoc.width()*ratio+170*ratio+i*35*ratio-((cardBack->width())/2)
		&& y > deckLoc.height()*ratio-((cardBack->height())/2) && y < deckLoc.height()*ratio+((cardBack->height())/2))
		if(mouseDown) //selecting
		{
			movingFromType = 1;
			board.moveCards(8, 1, 0, 0);
			return;
		}

		//if we're on one of the discard piles
		for(int i = 1; i < 5; i++)
		{
			if(x < suitsnapLocs[i].width()*ratio+((cardBack->width())/2) && x > suitsnapLocs[i].width()*ratio-((cardBack->width())/2)
				&& y < suitsnapLocs[i].height()*ratio+((cardBack->height())/2) && y > suitsnapLocs[i].height()*ratio-((cardBack->height())/2))
				if(board.getColumn(0).getSize() == 1)
					board.putUp(board.getColumn(0).getVal(0), 0);
		}


	//if we click on a column
	for(int i = 1; i < 8; i++) //There are better ways to do this than an iterative approach, but it works just as well.
	{
		cardColumn = board.getColumn(i);

		for(int j = (((cardColumn.getSize()-1) == -1) ? 0 : cardColumn.getSize()-1); j >= 0; j--)
			if(x < (snapLocs[i].width()*ratio+(cardBack->width()/2)) && x > (snapLocs[i].width()*ratio-(cardBack->width()/2))
				&& y < (snapLocs[i].height()*ratio+j*35*ratio+(cardBack->height()/2)) && y > (snapLocs[i].height()*ratio+j*35*ratio-(cardBack->height()/2)))
			{
				//At this point, i will be the column number (from the left) and j will be the depth in that column.

				if(mouseDown)
				{//we're selecting a fresh stack.
					if(cardColumn.getSize() > 0)
					{
						cardColumn=board.getColumn(i);
						if(cardColumn.getFlip(j)) //if this is a valid selection
						{
							board.moveCards(i, cardColumn.getSize()-j, 0, 0);
							movingFromType = 0;
							movingFrom=i;
						} else {
							board.flipColumn(i);
						}
					}
				}
				else
				{//we might be dropping a stack
					cardColumn=board.getColumn(0);
					//////////////BUG//////write in if(holding cards) check here
					if(!board.moveCards(0, cardColumn.getSize(), i, 1))  //try to move cards to the stack we're over
						returnCards(); //if that doesn't work, pop them back where they came from
				}
				return;
			}
	}

	//we only get to this point if we didn't find a valid stack to pull from or drop on.
	returnCards();

}

void SolGUI::returnCards()
{

	CardColumn cardColumn=board.getColumn(0);
	if (!mouseDown && cardColumn.getSize() > 0)
	{
		switch(movingFromType)
		{
		case 0:
			board.moveCards(0, cardColumn.getSize(), movingFrom, 0);
			break;
		case 1:
			board.moveCards(0, 1, 8, 0);
			break;
		}
	}

}

void SolGUI::resizeEvent(QResizeEvent *e)
{
	QString filename;
	string file;

	ratio = .7f*float(e->size().height() / float(768));

	QSize size(150*ratio, 215*ratio);

	for(int i = 0; i < 52; i++)
	{
		file = "resources/" + cardSuit(i) + "-" + cardValue(i) + "-150.png";
		cardImage[i].load(QString(file.c_str()));
		cardImage[i] = cardImage[i].scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	}

	cardBack->load("resources/back-red-150-1.png");

	suitBack[1].load("resources/diamonds.png");
	suitBack[2].load("resources/clubs.png");
	suitBack[3].load("resources/hearts.png");
	suitBack[4].load("resources/spades.png");

	for(int i = 1; i < 5; i++)
		suitBack[i] = suitBack[i].scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	
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