////////////////////////////////////////////////////////////////////////////////
// QtMain.h                                                                   //
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

#ifndef QTMAIN_H
#define QTMAIN_H

#include <vector>
#include <QMainWindow>

#include "SolGUI.h"

class SolMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	SolMainWindow();
	~SolMainWindow();

public Q_SLOTS:
	//The below are the trigger functions for all of the menu options.  They delegate control to SolGUI.
	void redealTrigger();
	void undoTrigger();
	void setDrawNumber1Trigger();
	void setDrawNumber3Trigger();
	void updateStatus();
	void updateOneSec();
	void changeBack(int);

private:
	//setup functions for our menus
	void createMenus();
	void createActions();

	SolGUI * SolGUIptr; //pointer to the SolGUI
	
	QSignalMapper * signalMapper; //used to map signals for cardback trigger calls

	//timers for our status update loop and game time
	QTimer * statusLoopTimer;
	QTimer * oneSecTimer;
	
	//menus
	QMenu * cardBackMenu;
	QMenu * drawMenu;

	//actions contained in the menus
	QAction * setDrawNumber1Act;
	QAction * setDrawNumber3Act;
	QAction * redealAct;
	QAction * undoAct;
	vector<QAction*> backAct;
};

#endif