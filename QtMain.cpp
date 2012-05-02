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
	
	for(int i = 0; i < 8; i++)
		backAct.push_back(new QAction(this));

	createActions();
	createMenus();

	backAct[0]->setChecked(true);

	setWindowTitle(tr("Solitaire GUI"));
	resize(900, 600);

	this->setStyleSheet("background-color: darkgreen;");

	setCentralWidget(SolGUIptr);

	statusLoopTimer = new QTimer;
	statusLoopTimer->start(500);
	connect(statusLoopTimer, SIGNAL(timeout()), this, SLOT(updateStatus()));

}

SolMainWindow::~SolMainWindow()
{
	delete SolGUIptr;
	delete signalMapper;
}

void SolMainWindow::updateStatus()
{
	stringstream ss;

	ss << "Score: " << SolGUIptr->getPlayerScore() << "      Time: " << SolGUIptr->getPlayedTime();
	statusBar()->showMessage(QString(ss.str().c_str()));

	statusLoopTimer->start(20);
}

void SolMainWindow::createMenus()
{
	menuBar()->setStyleSheet("background-color: gray;");

	menuBar()->addAction(redealAct);
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

	redealAct = new QAction(tr("&ReDeal"), this);
	connect(redealAct, SIGNAL(triggered()), this, SLOT(redealTrigger()));

	//All of the follow is the signal mapping code for the card back menu
	//  items.  We have to use a signal mapper because Qt's SIGNAL->SLOT
	//  ability sucks.
	for(int i = 0; i < backAct.size(); i++)
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
{
	for(unsigned int i = 0; i < backAct.size(); i++)
		backAct[i]->setChecked(false);

	backAct[backnumber]->setChecked(true);
	SolGUIptr->changeCardBack(backnumber);
}

void SolMainWindow::redealTrigger()
{
	SolGUIptr->redeal();
}