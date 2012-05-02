////////////////////////////////////////////////////////////////////////////////
// QtMain.cpp                                                                 //
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

#include <stdio.h>
#include <sstream>
#include <QMenuBar>

#include "QtMain.h"
#include "SolGUI.h"

using namespace std;

SolMainWindow::SolMainWindow()
{
	SolGUIptr = new SolGUI;
	signalMapper = new QSignalMapper;

	//setup our menus
	createActions();
	createMenus();

	backAct[0]->setChecked(true); //by default we use the normal cardbacks, so check it in the menu
	setDrawNumber3Act->setChecked(true); //default = draw 3 cards

	setWindowTitle(tr("Solitaire GUI"));
	resize(900, 600);

	this->setStyleSheet("background-color: darkgreen;");

	setCentralWidget(SolGUIptr); //main widget is our solitaire game

	//sets up timers for looping updates
	statusLoopTimer = new QTimer;
	statusLoopTimer->start(500);
	connect(statusLoopTimer, SIGNAL(timeout()), this, SLOT(updateStatus()));

	oneSecTimer = new QTimer;
	oneSecTimer->start(1000);
	connect(oneSecTimer, SIGNAL(timeout()), this, SLOT(updateOneSec()));

}

SolMainWindow::~SolMainWindow()
{
	delete SolGUIptr;
	delete signalMapper;
	delete oneSecTimer;
	delete statusLoopTimer;
}

void SolMainWindow::updateStatus()
{//called every 20ms to pull current game stats from SolGUI and update them in the gui
	stringstream ss;

	ss << "Score(not working yet): " << SolGUIptr->getPlayerScore() << "      Time: " << SolGUIptr->getPlayedTime();
	statusBar()->showMessage(QString(ss.str().c_str()));

	statusLoopTimer->start(20);
}

void SolMainWindow::updateOneSec()
{//calls solgui to update game time every second
	SolGUIptr->incrementPlayerTime();
	oneSecTimer->start(1000);
}

void SolMainWindow::createMenus()
{
	//this adds all of our menu functions
	menuBar()->setStyleSheet("background-color: gray;");

	menuBar()->addAction(redealAct);
	menuBar()->addAction(undoAct);
	drawMenu = menuBar()->addMenu(tr("&Draw Number"));
	drawMenu->addAction(setDrawNumber1Act);
	drawMenu->addAction(setDrawNumber3Act);

	cardBackMenu = menuBar()->addMenu(tr("&Card Backs"));
	cardBackMenu->setPalette(*(new QPalette(Qt::gray)));
	for(unsigned int i = 0; i < backAct.size(); i++)
	{
		cardBackMenu->addAction(backAct[i]);
	}
}

void SolMainWindow::createActions()
{
	stringstream ss;

	//the followed code sets up all the menu actions
	redealAct = new QAction(tr("&ReDeal"), this);
	connect(redealAct, SIGNAL(triggered()), this, SLOT(redealTrigger()));

	undoAct = new QAction(tr("&Undo"), this);
	undoAct->setShortcuts(QKeySequence::Undo);
	connect(undoAct, SIGNAL(triggered()), this, SLOT(undoTrigger()));

	setDrawNumber1Act = new QAction(tr("&Draw 1"), this);
	setDrawNumber1Act->setCheckable(true);
	connect(setDrawNumber1Act, SIGNAL(triggered()), this, SLOT(setDrawNumber1Trigger()));
	setDrawNumber3Act = new QAction(tr("&Draw 3"), this);
	setDrawNumber3Act->setCheckable(true);
	connect(setDrawNumber3Act, SIGNAL(triggered()), this, SLOT(setDrawNumber3Trigger()));

	//set the number of actions we want automatically generated in backAct by changing i
	for(int i = 0; i < 8; i++)
		backAct.push_back(new QAction(this));

	//All of the follow is the signal mapping code for the card back menu
	//  items.  We have to use a signal mapper because Qt's SIGNAL->SLOT
	//  ability sucks.
	for(unsigned int i = 0; i < backAct.size(); i++)
	{//map each menu action to a signal
		ss.str("");
		ss << ((i/4) > 0 ? "Blue" : "Red") << " Card Back " << i+1;
		backAct[i] = new QAction(tr(ss.str().c_str()), this);
		connect(backAct[i], SIGNAL(triggered()), signalMapper, SLOT(map()));
		signalMapper->setMapping(backAct[i] , i);
	}
	//set checkable true
	for(unsigned int i = 0; i < backAct.size(); i++)
		backAct[i]->setCheckable(true);
	//map the signals to the function
	connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(changeBack(int)));
}

void SolMainWindow::changeBack(int backnumber)
{//trigger function for changing card back
	for(unsigned int i = 0; i < backAct.size(); i++)
		backAct[i]->setChecked(false);

	backAct[backnumber]->setChecked(true);
	SolGUIptr->changeCardBack(backnumber);
}

void SolMainWindow::redealTrigger()
{//trigger for redealing cards
	SolGUIptr->redeal();
}

void SolMainWindow::undoTrigger()
{//trigger for undoing a move
	SolGUIptr->undo();
}

void SolMainWindow::setDrawNumber1Trigger()
{//trigger for setting drawNumber to 1
	setDrawNumber3Act->setChecked(false);
	setDrawNumber1Act->setChecked(true);
	SolGUIptr->setDrawNumber1();
}

void SolMainWindow::setDrawNumber3Trigger()
{//trigger for setting drawNumber to 3
	setDrawNumber1Act->setChecked(false);
	setDrawNumber3Act->setChecked(true);
	SolGUIptr->setDrawNumber3();
}